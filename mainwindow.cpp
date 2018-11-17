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
    PressManagerDlg = NULL;
    BookManagerDlg = NULL;
}
//yu
MainWindow::~MainWindow()
{
    delete ui;
}
//wu

void MainWindow::on_BtnBorrow_clicked()
{
    BkrDlg=new BorrowBookDlg(this);
    BkrDlg->show();
}
void MainWindow::on_BtnPressManager_clicked()
{
    if(PressManagerDlg == NULL)
    {
        PressManagerDlg = new PressManagerDialog(this);
        PressManagerDlg->setModal(false);
    }
    PressManagerDlg->show();
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

void MainWindow::on_BtnReturn_clicked()
{
    pReturnDlg=new ReturnBookDlg(this);
    pReturnDlg->show();
}

void MainWindow::on_BtnBookManager_clicked()
{
    if(BookManagerDlg == NULL)
    {
        BookManagerDlg = new bookmanagerDialog(this);
        BookManagerDlg->setModal(false);
    }
    BookManagerDlg->show();
}
