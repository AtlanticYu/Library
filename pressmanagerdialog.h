#ifndef PRESSMANAGERDIALOG_H
#define PRESSMANAGERDIALOG_H

#include <QDialog>
#include <onepressdialog.h>

namespace Ui {
class PressManagerDialog;
}

class PressManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PressManagerDialog(QWidget *parent = nullptr);
    ~PressManagerDialog();

protected:
    void showEvent (QShowEvent * event);
    void showAllPress();

private slots:
    void on_BtnPressModify_clicked();

    void on_BtnPressDelete_clicked();

    void on_BtnAddPress_clicked();

    void AddPress(QString,QString);

private:
    Ui::PressManagerDialog *ui;
    OnePressDialog *OnePressDlg;
};

#endif // PRESSMANAGERDIALOG_H
