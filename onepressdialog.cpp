#include "onepressdialog.h"
#include "ui_onepressdialog.h"

OnePressDialog::OnePressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OnePressDialog)
{
    ui->setupUi(this);
}

OnePressDialog::~OnePressDialog()
{
    delete ui;
}

void OnePressDialog::on_BtnClose_clicked()
{
    this->accept();
}

void OnePressDialog::on_BtnCommit_clicked()
{
    //给上一层发送信号
    emit SendPress(ui->EdtPressName->text(),ui->EdtPressAddress->text());
}
