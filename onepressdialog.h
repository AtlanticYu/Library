#ifndef ONEPRESSDIALOG_H
#define ONEPRESSDIALOG_H

#include <QDialog>

namespace Ui {
class OnePressDialog;
}

class OnePressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OnePressDialog(QWidget *parent = nullptr);
    ~OnePressDialog();

private slots:
    void on_BtnClose_clicked();

    void on_BtnCommit_clicked();

private:
    Ui::OnePressDialog *ui;
signals:
    void AddPress(QString,QString);
};

#endif // ONEPRESSDIALOG_H
