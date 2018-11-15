#include "onebookdialog.h"
#include "ui_onebookdialog.h"

OneBookDialog::OneBookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OneBookDialog)
{
    ui->setupUi(this);
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
    emit SendBook(ui->EdtBookName->text(),ui->EdtPressId->text(),ui->EdtPressName->text(),ui->EdtPressDate->text());
}


