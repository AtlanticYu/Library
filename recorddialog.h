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
    int myOperationgStyle;//0 aLL,1 user,2 book
};

#endif // RECORDDIALOG_H
