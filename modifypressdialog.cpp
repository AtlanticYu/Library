#include "modifypressdialog.h"
#include "ui_modifypressdialog.h"
#include "QMessageBox"
#include "sqlite3.h"

ModifyPressDialog::ModifyPressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyPressDialog)
{
    ui->setupUi(this);
}

ModifyPressDialog::~ModifyPressDialog()
{
    delete ui;
}

void ModifyPressDialog::on_BtnClose_clicked()
{
    this->accept();
}

void ModifyPressDialog::GetBeforePress(QString press_id,QString press_name,QString press_address)
{
    ui->EdtPressName->setText(press_name);
    ui->EdtPressAddress->setText(press_address);
    NeedModifyPressId = press_id;
}

void ModifyPressDialog::on_BtnCommit_clicked()
{
    QString press_name = ui->EdtPressName->text();
    QString press_address = ui->EdtPressAddress->text();
    if(press_name == NULL || press_address == NULL)
    {
        QMessageBox::information(this,"错误","没有正确输入相应信息");
        return;
    }
    sqlite3 *pDb;
    if(sqlite3_open("./MyLibrary.db",&pDb)!=SQLITE_OK) return;
    QString sql = "update T_PRESS set press_name = '"+press_name+"',press_address = '"+press_address+"' where press_id = '"+NeedModifyPressId+"';";
    char *errmsg;
    if(sqlite3_exec(pDb,sql.toStdString().c_str(),NULL,NULL,&errmsg)==SQLITE_OK)
    {
        QMessageBox::information(this,"提示","修改成功");
    }
    sqlite3_close(pDb);
    emit NotifyRefleshPressTable();
}
