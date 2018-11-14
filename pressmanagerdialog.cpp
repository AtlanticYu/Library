#include "pressmanagerdialog.h"
#include "ui_pressmanagerdialog.h"
#include "onepressdialog.h"
#include "QMessageBox"
#include "sqlite3.h"

PressManagerDialog::PressManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PressManagerDialog)
{
    ui->setupUi(this);
    OnePressDlg = NULL;
}

PressManagerDialog::~PressManagerDialog()
{
    delete ui;
}

void PressManagerDialog::on_BtnPressModify_clicked()
{

}

//根据用户所点击的一条数据来进行删除
void PressManagerDialog::on_BtnPressDelete_clicked()
{
    //获取当前选中行数
    int row = ui->tableWidgetPress->currentRow();
    if(row > 0)
    {
        QTableWidgetItem *pIdItem = ui->tableWidgetPress->item(row,0);
        sqlite3 *pDb;
        QString id = pIdItem->text();
        if(sqlite3_open("./MyLibrary.db",&pDb)!=SQLITE_OK) return;
        QString sql = "delete from T_PRESS where press_id = '"+id+"';";
        char *errmsg;
        if(sqlite3_exec(pDb,sql.toStdString().c_str(),NULL,NULL,&errmsg)==SQLITE_OK)
        {
            ui->tableWidgetPress->removeRow(row);
        }
        sqlite3_close(pDb);
    }
}

//添加一个出版社
void PressManagerDialog::on_BtnAddPress_clicked()
{
    if(OnePressDlg==NULL) {
        OnePressDlg = new OnePressDialog(this);
        OnePressDlg->setModal(false);
        connect(OnePressDlg,SIGNAL(AddPress(QString,QString)),this,SLOT(AddPress(QString,QString)));
    }
    OnePressDlg->show();
}

void PressManagerDialog::AddPress(QString press_name,QString press_address)
{
    //判断是否为空
    if(press_name ==NULL||press_address == NULL)
    {
        QMessageBox::information(this,"错误","没有正确输入相应信息");
        return;
    }
    //写入数据库
    sqlite3 *pDb;
    if(sqlite3_open("./MyLibrary.db",&pDb)!=SQLITE_OK) return;
    QString sql = "insert into T_PRESS(press_name,press_address) values('"+press_name+"','"+press_address+"')";
    char *errmsg;
    sqlite3_exec(pDb,sql.toStdString().c_str(),NULL,NULL,&errmsg);
    sqlite3_close(pDb);
    //本地更新
    showAllPress();
}

//窗口显示前加载所有出版社信息
void PressManagerDialog::showEvent(QShowEvent * event)
{
    showAllPress();
}

void PressManagerDialog::showAllPress()
{
    //添加首先要清空，否则会重复插入
    int Tcount = ui->tableWidgetPress->rowCount();
    for(int i = 0;i < Tcount;i ++ )
    {
        ui->tableWidgetPress->removeRow(0);
    }

    sqlite3 *pDb;
    if(sqlite3_open("./MyLibrary.db",&pDb) == SQLITE_OK)
    {
        //反序是因为数据是insert插入到第一行的
        QString sql = "select * from T_PRESS order by press_id desc";
        sqlite3_stmt *pStmt;
        if(sqlite3_prepare(pDb,sql.toStdString().c_str(),sql.length(),&pStmt,NULL) == SQLITE_OK)
        {
            while(sqlite3_step(pStmt) == SQLITE_ROW)
            {
                const unsigned char *p_press_id = sqlite3_column_text(pStmt,0);
                const unsigned char *p_press_name = sqlite3_column_text(pStmt,1);
                const unsigned char *p_press_address = sqlite3_column_text(pStmt,2);
                QTableWidgetItem *pIdItem = new QTableWidgetItem((char *)p_press_id);
                ui->tableWidgetPress->insertRow(0);
                ui->tableWidgetPress->setItem(0,0,pIdItem);
                QTableWidgetItem *pNameItem = new QTableWidgetItem((char *)p_press_name);
                ui->tableWidgetPress->setItem(0,1,pNameItem);
                QTableWidgetItem *pAddressItem = new QTableWidgetItem((char *)p_press_address);
                ui->tableWidgetPress->setItem(0,2,pAddressItem);
                //QTableWidget根据内容调整列宽
                ui->tableWidgetPress->resizeColumnsToContents();
            }
        }
        sqlite3_close(pDb);
    }
}


