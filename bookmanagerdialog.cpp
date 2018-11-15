#include "bookmanagerdialog.h"
#include "ui_bookmanagerdialog.h"

bookmanagerDialog::bookmanagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bookmanagerDialog)
{
    ui->setupUi(this);
}

bookmanagerDialog::~bookmanagerDialog()
{
    delete ui;
}
