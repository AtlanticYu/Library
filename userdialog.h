#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include<QDebug>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include <QMessageBox>
#include<sqlite3.h>
#include"userupdatedialog.h"

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

    void on_pushButton_Delete_clicked();

    void on_pushButton_Update_clicked();
    void refreshTable();
signals:
    void sendMyRow(QString ,QString ,QString);
private:
    Ui::UserDialog *ui;
    QSqlQueryModel *model;
    UserUpdateDialog *pUserUpdateDlg;
    int mymodel;

};

#endif // USERDIALOG_H
