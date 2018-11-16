#ifndef BOOKMANAGERDIALOG_H
#define BOOKMANAGERDIALOG_H

#include <QDialog>
#include <onebookdialog.h>
#include <modifybookdialog.h>

namespace Ui {
class bookmanagerDialog;
}

class bookmanagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit bookmanagerDialog(QWidget *parent = nullptr);
    ~bookmanagerDialog();

protected:
    void showEvent (QShowEvent * event);
    void showAllBooks();

private slots:
    void on_BtnSearch_clicked();

    void on_BtnReload_clicked();

    void on_BtnBookDelete_clicked();

    void on_BtnBookModify_clicked();

    void ReceiveRefleshSignal();

    void on_BtnAddBook_clicked();

    void GetBook(QString,QString,QString,QString);

private:
    Ui::bookmanagerDialog *ui;
    OneBookDialog *oneBookDlg;
    ModifyBookDialog *modifyBookDlg;

signals:
    void SendClickedBook(QString,QString,QString,QString,QString);
};

#endif // BOOKMANAGERDIALOG_H
