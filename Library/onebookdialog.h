#ifndef ONEBOOKDIALOG_H
#define ONEBOOKDIALOG_H

#include <QDialog>
#include <QComboBox>

namespace Ui {
class OneBookDialog;
}

class OneBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OneBookDialog(QWidget *parent = nullptr);
    ~OneBookDialog();
    void initComboBox();


private slots:
    void on_BtnCancel_clicked();

    void on_BtnAddBook_clicked();

    void on_CbxAllPress_currentIndexChanged(const QString &arg1);

    void showMatchId();

private:
    Ui::OneBookDialog *ui;
    int InitStatus = 0;

signals:
    void SendBook(QString,QString,QString,QString);

};

#endif // ONEBOOKDIALOG_H
