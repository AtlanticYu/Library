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

private:
    Ui::ModifyBookDialog *ui;
};

#endif // MODIFYBOOKDIALOG_H
