#include "modifybookdialog.h"
#include "ui_modifybookdialog.h"
#include "QMessageBox"
#include "sqlite3.h"

ModifyBookDialog::ModifyBookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyBookDialog)
{
    ui->setupUi(this);
}

ModifyBookDialog::~ModifyBookDialog()
{
    delete ui;
}

void ModifyBookDialog::on_BtnCancel_clicked()
{
    this->accept();
}

void ModifyBookDialog::on_BtnConfirmBook_clicked()
{
    QString book_name = ui->EdtBookName->text();
    QString press_id = ui->EdtPressId->text();
    QString press_name = ui->EdtPressName->text();
    QString press_date = ui->EdtPressDate->text();
    if(book_name == NULL||press_id == NULL||press_name == NULL||press_date ==NULL)
    {
        QMessageBox::information(this,"错误","没有正确输入相应信息");
        return;
    }
    sqlite3 *pDb;
    if(sqlite3_open("./MyLibrary.db",&pDb)!=SQLITE_OK) return;
    QString sql = "update T_BOOK set book_name = '"+book_name+"',press_time = '"+press_date+"' where book_id = '"+NeedModifyBookId+"';";
    char *errmsg;
    //中文要转成utf8
    if(sqlite3_exec(pDb,sql.toUtf8().data(),NULL,NULL,&errmsg)==SQLITE_OK)
    {
        QMessageBox::information(this,"提示","修改成功");
    }
    sqlite3_close(pDb);
    emit NotifyRefleshBookTable();

}

void ModifyBookDialog::GetBeforeBook(QString book_id,QString book_name,QString press_id,QString press_name,QString press_time)
{
    ui->EdtBookName->setText(book_name);
    ui->EdtPressId->setText(press_id);
    ui->EdtPressName->setText(press_name);
    ui->EdtPressDate->setText(press_time);
    NeedModifyBookId = book_id;
}
