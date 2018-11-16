#ifndef ONEBOOKDIALOG_H
#define ONEBOOKDIALOG_H

#include <QDialog>

namespace Ui {
class OneBookDialog;
}

class OneBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OneBookDialog(QWidget *parent = nullptr);
    ~OneBookDialog();

private slots:
    void on_BtnCancel_clicked();

    void on_BtnAddBook_clicked();


private:
    Ui::OneBookDialog *ui;

signals:
    void SendBook(QString,QString,QString,QString);

};

#endif // ONEBOOKDIALOG_H
