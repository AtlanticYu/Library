#include "modifybookdialog.h"
#include "ui_modifybookdialog.h"

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
