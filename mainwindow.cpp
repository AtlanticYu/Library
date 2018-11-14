#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pressmanagerdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
