#ifndef RETURNBOOKDLG_H
#define RETURNBOOKDLG_H

#include <QDialog>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include <QMessageBox>
#include<sqlite3.h>
namespace Ui {
class ReturnBookDlg;
}

class ReturnBookDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ReturnBookDlg(QWidget *parent = nullptr);
    ~ReturnBookDlg();

private slots:
    void on_BtnSelect_clicked();

    void on_BtnReturn_clicked();

private:
    Ui::ReturnBookDlg *ui;
    QSqlQueryModel *model;
    int mymodel;
};

#endif // RETURNBOOKDLG_H
