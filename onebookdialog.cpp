#include "onebookdialog.h"
#include "ui_onebookdialog.h"
#include "QComboBox"
#include "sqlite3.h"

OneBookDialog::OneBookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OneBookDialog)
{
    ui->setupUi(this);
    initComboBox();
    connect(ui->CbxAllPress,SIGNAL(currentIndexChanged(QString)),this,SLOT(FillPressId()));
}

OneBookDialog::~OneBookDialog()
{
    delete ui;
}

void OneBookDialog::on_BtnCancel_clicked()
{
    this->accept();
}

void OneBookDialog::on_BtnAddBook_clicked()
{
    //给上一层发送信号
    emit SendBook(ui->EdtBookName->text(),ui->EdtPressId->text(),ui->CbxAllPress->currentText(),ui->EdtPressDate->text());
}

//初始化ComboBox的值
void OneBookDialog::initComboBox()
{
    sqlite3 *pDb;
    if(sqlite3_open("./MyLibrary.db",&pDb) == SQLITE_OK)
    {
        QString sql = "select press_name from T_PRESS";
        sqlite3_stmt *pStmt;
        if(sqlite3_prepare(pDb,sql.toStdString().c_str(),sql.length(),&pStmt,NULL) == SQLITE_OK)
        {
            while(sqlite3_step(pStmt) == SQLITE_ROW)
            {
                const unsigned char *p_press_name = sqlite3_column_text(pStmt,0);
                std::string str = (char *)p_press_name;
                QString press_name = QString::fromStdString(str);
                ui->CbxAllPress->addItem(press_name);
            }
        }
        sqlite3_close(pDb);
        InitStatus = 1;
    }
}


//清除会引发错误
void OneBookDialog::on_CbxAllPress_currentIndexChanged(const QString &arg1)
{

}

//当ComboBox改变值时到数据库匹配
void OneBookDialog::FillPressId()
{
    sqlite3 *pDb;
    QString press_name = ui->CbxAllPress->currentText();
    //因为初始化每次都会激活相应的槽，为了避免数据库的同时打开
    if(InitStatus == 1)
    {
        if(sqlite3_open("./MyLibrary.db",&pDb) == SQLITE_OK)
        {
            QString sql = "select * from T_PRESS where press_name = '"+press_name+"'";
            sqlite3_stmt *pStmt;
            //查询中文要转成utf8，其中第二、三个参数都需要做相应修改，不转码会查询失败
            if(sqlite3_prepare(pDb,sql.toUtf8().data(),sql.toUtf8().length(),&pStmt,NULL) == SQLITE_OK)
//            if(sqlite3_prepare(pDb,sql.toStdString().c_str(),sql.length(),&pStmt,NULL) == SQLITE_OK)
            {
               while(sqlite3_step(pStmt) == SQLITE_ROW)
               {
                    const unsigned char *p_press_id = sqlite3_column_text(pStmt,0);
                    QString press_id = (char *)p_press_id;
                    ui->EdtPressId->setText(press_id);
               }
            }
            sqlite3_close(pDb);
        }
    }
}
