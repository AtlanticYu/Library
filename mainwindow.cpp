#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_BtnBorrow_clicked()
{
    BkrDlg=new BorrowBookDlg(this);
    BkrDlg->show();
}
