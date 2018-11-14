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
