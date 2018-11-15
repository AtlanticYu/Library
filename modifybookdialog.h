#ifndef MODIFYBOOKDIALOG_H
#define MODIFYBOOKDIALOG_H

#include <QDialog>

namespace Ui {
class ModifyBookDialog;
}

class ModifyBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyBookDialog(QWidget *parent = nullptr);
    ~ModifyBookDialog();

private slots:
    void on_BtnCancel_clicked();

    void on_BtnConfirmBook_clicked();

    void GetBeforeBook(QString,QString,QString,QString,QString);

private:
    Ui::ModifyBookDialog *ui;
    QString NeedModifyBookId;

signals:
    void NotifyRefleshBookTable();
};

#endif // MODIFYBOOKDIALOG_H
