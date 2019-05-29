#include "userupdatedialog.h"
#include "ui_userupdatedialog.h"

UserUpdateDialog::UserUpdateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserUpdateDialog)
{
    ui->setupUi(this);

}

UserUpdateDialog::~UserUpdateDialog()
{
    delete ui;
}

void UserUpdateDialog::getMessage(QString user_id,QString user_name,QString user_status)
{
    ui->lineEdit_UserId->setText(user_id);
    ui->lineEdit_UserName->setText(user_name);
    ui->lineEdit_UserStatus->setText(user_status);
}

void UserUpdateDialog::on_pushButton_Update_clicked()
{
      USER_NAME=ui->lineEdit_UserName->text();
      this->accept();
}

void UserUpdateDialog::on_pushButton_Close_clicked()
{
    this->close();
}
