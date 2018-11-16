#ifndef RECORDDIALOG_H
#define RECORDDIALOG_H

#include <QDialog>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QMessageBox>
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
    QSqlQueryModel *model;
    int mymodel;
    int myOperationgStyle;//0 aLL,1 user,2 book
};

#endif // RECORDDIALOG_H
