#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pRecordDlg=NULL;
    pUserDlg=NULL;
}
//yu
MainWindow::~MainWindow()
{
    delete ui;
}
//wu

void MainWindow::on_BtnRecordManager_clicked()
{
    if(pRecordDlg==NULL) {
        pRecordDlg = new RecordDialog(this);
        pRecordDlg->setModal(false);
    }
    pRecordDlg->show();
}

void MainWindow::on_BtnUserManager_clicked()
{
    if(pUserDlg==NULL) {
        pUserDlg = new UserDialog(this);
        pUserDlg->setModal(false);
    }
    pUserDlg->show();

}
