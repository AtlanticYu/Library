#ifndef RECORDDIALOG_H
#define RECORDDIALOG_H

#include <QDialog>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include <QMessageBox>
#include<sqlite3.h>

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


private:
    Ui::RecordDialog *ui;
    QSqlQueryModel *model;
    int mymodel;
};

#endif // RECORDDIALOG_H
