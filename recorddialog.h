#ifndef RECORDDIALOG_H
#define RECORDDIALOG_H

#include <QDialog>
#include<QSqlQuery>
#include<QSqlTableModel>
#include <QMessageBox>
#include<QStandardItem>
#include"printviewdialog.h"
#include<sqlite3.h>
#include<QDebug>
#include"dbManager.h"

namespace Ui {
class RecordDialog;
}

class RecordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RecordDialog(QWidget *parent = nullptr);
    ~RecordDialog();
    int getStatus();
    void  screen1();
    void  screen2();
    void  screen3();
    void  screen4();
    void  screen5();
    void  screen6();
    void  screen7();

    void  screen11();
    void  screen22();
    void  screen33();
    void  screen44();
    void  screen55();
    void  screen66();
    void  screen77();

    void  screen111();
    void  screen222();
    void  screen333();
    void  screen444();
    void  screen555();
    void  screen666();
    void  screen777();

private slots:
    void on_pushButton_UserId_clicked();

    void on_pushButton_BookId_clicked();

    void on_pushButton_ShowAll_clicked();

    void on_pushButton_screen_clicked();


    void on_pushButton_ShowPdf_clicked();
signals:
    void sendMyHtml(QString);

private:
    Ui::RecordDialog *ui;
    QSqlTableModel *model;
    int mymodel;
    int myOperationgStyle;//0 aLL,1 user,2 book
    QSqlDatabase db;
};

#endif // RECORDDIALOG_H
