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
