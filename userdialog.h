#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include <QMessageBox>
#include<sqlite3.h>

namespace Ui {
class UserDialog;
}

class UserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserDialog(QWidget *parent = nullptr);
    ~UserDialog();

private slots:

    void on_pushButton_AddUser_clicked();

    void on_pushButton_ShowAll_clicked();

private:
    Ui::UserDialog *ui;
    QSqlQueryModel *model;
};

#endif // USERDIALOG_H
