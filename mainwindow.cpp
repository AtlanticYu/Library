#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pressmanagerdialog.h"
#include "bookmanagerdialog.h"

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

void MainWindow::on_BtnPressManager_clicked()
{
    PressManagerDialog PressDlg(this);
    PressDlg.setModal(true);
    PressDlg.exec();
}
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

void MainWindow::on_BtnBookManager_clicked()
{
    bookmanagerDialog BookDlg(this);
    BookDlg.setModal(true);
    BookDlg.exec();
}
