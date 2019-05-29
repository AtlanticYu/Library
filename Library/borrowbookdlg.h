#ifndef BORROWBOOKDLG_H
#define BORROWBOOKDLG_H

#include <QDialog>
#include <QSqlQuery>
namespace Ui {
class BorrowBookDlg;
}

class BorrowBookDlg : public QDialog
{
    Q_OBJECT

public:
    explicit BorrowBookDlg(QWidget *parent = nullptr);
    ~BorrowBookDlg();

protected:
    void ShowBook();

private slots:
    void on_Btnsearch_clicked();

    void on_BtnBorrow_clicked();

private:
    Ui::BorrowBookDlg *ui;
};

#endif // BORROWBOOKDLG_H
