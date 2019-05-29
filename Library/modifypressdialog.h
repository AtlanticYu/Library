#ifndef MODIFYPRESSDIALOG_H
#define MODIFYPRESSDIALOG_H

#include <QDialog>

namespace Ui {
class ModifyPressDialog;
}

class ModifyPressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyPressDialog(QWidget *parent = nullptr);
    ~ModifyPressDialog();

private slots:
    void on_BtnClose_clicked();

    void GetBeforePress(QString,QString,QString);

    void on_BtnCommit_clicked();

signals:
    void NotifyRefleshPressTable();

private:
    Ui::ModifyPressDialog *ui;
    QString NeedModifyPressId;
};

#endif // MODIFYPRESSDIALOG_H
