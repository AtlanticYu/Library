#include "bookmanagerdialog.h"
#include "ui_bookmanagerdialog.h"
#include "QMessageBox"
#include "sqlite3.h"

bookmanagerDialog::bookmanagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bookmanagerDialog)
{
    ui->setupUi(this);
    oneBookDlg = NULL;
    modifyBookDlg = NULL;
}

bookmanagerDialog::~bookmanagerDialog()
{
    delete ui;
}

void bookmanagerDialog::showEvent (QShowEvent * event)
{
    showAllBooks();
}


void bookmanagerDialog::on_BtnSearch_clicked()
{
    QString bookname = ui->EdtInputBook->text();
    if(bookname == NULL)
    {
        QMessageBox::information(this,"错误","没有正确输入相应信息");
        return;
    }
    sqlite3 *pDb;
    if(sqlite3_open("./MyLibrary.db",&pDb) == SQLITE_OK)
    {
        QString sql = "select * from T_BOOK where book_name LIKE '%"+bookname+"%' order by book_id desc";
        sqlite3_stmt *pStmt;
        if(sqlite3_prepare(pDb,sql.toStdString().c_str(),sql.length(),&pStmt,NULL) == SQLITE_OK)
        {
            int Tcount = ui->tableWidgetBook->rowCount();
            for(int i = 0;i < Tcount;i ++ )
            {
                ui->tableWidgetBook->removeRow(0);
            }
            while(sqlite3_step(pStmt) == SQLITE_ROW)
            {
                const unsigned char *p_book_id = sqlite3_column_text(pStmt,0);
                const unsigned char *p_book_name = sqlite3_column_text(pStmt,1);
                const unsigned char *p_press_id = sqlite3_column_text(pStmt,2);
                const unsigned char *p_press_name = sqlite3_column_text(pStmt,3);
                const unsigned char *p_press_time = sqlite3_column_text(pStmt,4);
                const unsigned char *p_book_status = sqlite3_column_text(pStmt,5);
                QTableWidgetItem *pBookIdItem = new QTableWidgetItem((char *)p_book_id);
                ui->tableWidgetBook->insertRow(0);
                ui->tableWidgetBook->setItem(0,0,pBookIdItem);
                QTableWidgetItem *pBookNameItem = new QTableWidgetItem((char *)p_book_name);
                ui->tableWidgetBook->setItem(0,1,pBookNameItem);
                QTableWidgetItem *pPressIdItem = new QTableWidgetItem((char *)p_press_id);
                ui->tableWidgetBook->setItem(0,2,pPressIdItem);
                QTableWidgetItem *pPressNameItem = new QTableWidgetItem((char *)p_press_name);
                ui->tableWidgetBook->setItem(0,3,pPressNameItem);
                QTableWidgetItem *pPressTimeItem = new QTableWidgetItem((char *)p_press_time);
                ui->tableWidgetBook->setItem(0,4,pPressTimeItem);
                QTableWidgetItem *pPressStatusItem = new QTableWidgetItem((char *)p_book_status);
                QTableWidgetItem *pPressStatusItemTwo = new QTableWidgetItem((char *)"在库");
                QTableWidgetItem *pPressStatusItemThree = new QTableWidgetItem((char *)"已借出");
                QString book_status = pPressStatusItem->text();
                if(book_status == "0")
                {
                    ui->tableWidgetBook->setItem(0,5,pPressStatusItemTwo);
                }
                else
                {
                    ui->tableWidgetBook->setItem(0,5,pPressStatusItemThree);
                }
                //QTableWidget根据内容调整列宽
                ui->tableWidgetBook->resizeColumnsToContents();
            }
        }
    }

}

//加载所有图书到表中
void bookmanagerDialog::showAllBooks()
{
    int Tcount = ui->tableWidgetBook->rowCount();
    for(int i = 0;i < Tcount;i ++ )
    {
        ui->tableWidgetBook->removeRow(0);
    }

    sqlite3 *pDb;
    if(sqlite3_open("./MyLibrary.db",&pDb) == SQLITE_OK)
        {
            //反序是因为数据是insert插入到第一行的
            QString sql = "select * from T_BOOK order by book_id desc";
            sqlite3_stmt *pStmt;
            if(sqlite3_prepare(pDb,sql.toStdString().c_str(),sql.length(),&pStmt,NULL) == SQLITE_OK)
            {
                while(sqlite3_step(pStmt) == SQLITE_ROW)
                {
                    const unsigned char *p_book_id = sqlite3_column_text(pStmt,0);
                    const unsigned char *p_book_name = sqlite3_column_text(pStmt,1);
                    const unsigned char *p_press_id = sqlite3_column_text(pStmt,2);
                    const unsigned char *p_press_name = sqlite3_column_text(pStmt,3);
                    const unsigned char *p_press_time = sqlite3_column_text(pStmt,4);
                    const unsigned char *p_book_status = sqlite3_column_text(pStmt,5);
                    QTableWidgetItem *pBookIdItem = new QTableWidgetItem((char *)p_book_id);
                    ui->tableWidgetBook->insertRow(0);
                    ui->tableWidgetBook->setItem(0,0,pBookIdItem);
                    QTableWidgetItem *pBookNameItem = new QTableWidgetItem((char *)p_book_name);
                    ui->tableWidgetBook->setItem(0,1,pBookNameItem);
                    QTableWidgetItem *pPressIdItem = new QTableWidgetItem((char *)p_press_id);
                    ui->tableWidgetBook->setItem(0,2,pPressIdItem);
                    QTableWidgetItem *pPressNameItem = new QTableWidgetItem((char *)p_press_name);
                    ui->tableWidgetBook->setItem(0,3,pPressNameItem);
                    QTableWidgetItem *pPressTimeItem = new QTableWidgetItem((char *)p_press_time);
                    ui->tableWidgetBook->setItem(0,4,pPressTimeItem);
                    QTableWidgetItem *pPressStatusItem = new QTableWidgetItem((char *)p_book_status);
                    QTableWidgetItem *pPressStatusItemTwo = new QTableWidgetItem((char *)"在库");
                    QTableWidgetItem *pPressStatusItemThree = new QTableWidgetItem((char *)"已借出");
                    QString book_status = pPressStatusItem->text();
                    if(book_status == "0")
                    {
                        ui->tableWidgetBook->setItem(0,5,pPressStatusItemTwo);
                    }
                    else
                    {
                        ui->tableWidgetBook->setItem(0,5,pPressStatusItemThree);
                    }
                    //QTableWidget根据内容调整列宽
                    ui->tableWidgetBook->resizeColumnsToContents();
                }
            }
            sqlite3_close(pDb);
        }
}

//模糊查询后需要的返回初始状态
void bookmanagerDialog::on_BtnReload_clicked()
{
    showAllBooks();
}

//修改窗体提交后需要的刷新
void bookmanagerDialog::ReceiveRefleshSignal()
{
    showAllBooks();
}

//删除所选图书
void bookmanagerDialog::on_BtnBookDelete_clicked()
{
    //获取选中行数
    int row = ui->tableWidgetBook->currentRow();
    if(row >= 0)
    {
        QTableWidgetItem *pIdItem = ui->tableWidgetBook->item(row,0);
        sqlite3 *pDb;
        QString id = pIdItem->text();
        if(sqlite3_open("./MyLibrary.db",&pDb)!=SQLITE_OK) return;
        QString sql = "delete from T_BOOK where book_id = '"+id+"';";
        char *errmsg;
        if(sqlite3_exec(pDb,sql.toStdString().c_str(),NULL,NULL,&errmsg)==SQLITE_OK)
        {
            ui->tableWidgetBook->removeRow(row);
        }
        sqlite3_close(pDb);
    }
}

void bookmanagerDialog::on_BtnBookModify_clicked()
{
    //信号发给修改窗体的槽
    if(modifyBookDlg==NULL) {
        modifyBookDlg = new ModifyBookDialog(this);
        modifyBookDlg->setModal(false);
        // connect()函数来将某个对象的信号与另外一个对象的槽函数相关联，这样当发射者发射信号时，接收者的槽函数将被调用(发送者，信号，接收者，槽)
        connect(this,SIGNAL(SendClickedBook(QString,QString,QString,QString,QString)),modifyBookDlg,SLOT(GetBeforeBook(QString,QString,QString,QString,QString)));
        connect(modifyBookDlg,SIGNAL(NotifyRefleshBookTable()),this,SLOT(ReceiveRefleshSignal()));
    }
    int CurrentRow = ui->tableWidgetBook->currentRow();
    if (CurrentRow >= 0)
    {
        emit SendClickedBook(ui->tableWidgetBook->item(CurrentRow,0)->text(),ui->tableWidgetBook->item(CurrentRow,1)->text(),ui->tableWidgetBook->item(CurrentRow,2)->text(),ui->tableWidgetBook->item(CurrentRow,3)->text(),ui->tableWidgetBook->item(CurrentRow,4)->text());
    }
    modifyBookDlg->show();
}

void bookmanagerDialog::on_BtnAddBook_clicked()
{
    if(oneBookDlg==NULL) {
        oneBookDlg = new OneBookDialog(this);
        oneBookDlg->setModal(false);
        connect(oneBookDlg,SIGNAL(SendBook(QString,QString,QString,QString)),this,SLOT(GetBook(QString,QString,QString,QString)));
    }
    oneBookDlg->show();
}

void bookmanagerDialog::GetBook(QString book_name,QString press_id,QString press_name,QString press_time)
{
    //判断是否为空
    if(book_name ==NULL||press_id == NULL||press_name ==NULL||press_time == NULL)
    {
        QMessageBox::information(this,"错误","没有正确输入相应信息");
        return;
    }
    //写入数据库
    sqlite3 *pDb;
    if(sqlite3_open("./MyLibrary.db",&pDb)!=SQLITE_OK) return;
    QString sql = "insert into T_BOOK(book_name,press_id,press_name,press_time) values('"+book_name+"','"+press_id+"','"+press_name+"','"+press_time+"')";
    char *errmsg;
    sqlite3_exec(pDb,sql.toStdString().c_str(),NULL,NULL,&errmsg);
    sqlite3_close(pDb);
    //本地更新
    showAllBooks();
}
