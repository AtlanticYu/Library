#ifndef USERUPDATEDIALOG_H
#define USERUPDATEDIALOG_H

#include <QDialog>

namespace Ui {
class UserUpdateDialog;
}

class UserUpdateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserUpdateDialog(QWidget *parent = nullptr);
    ~UserUpdateDialog();

private:
    Ui::UserUpdateDialog *ui;
};

#endif // USERUPDATEDIALOG_H
