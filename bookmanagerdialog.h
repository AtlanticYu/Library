#ifndef BOOKMANAGERDIALOG_H
#define BOOKMANAGERDIALOG_H

#include <QDialog>

namespace Ui {
class bookmanagerDialog;
}

class bookmanagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit bookmanagerDialog(QWidget *parent = nullptr);
    ~bookmanagerDialog();

private:
    Ui::bookmanagerDialog *ui;
};

#endif // BOOKMANAGERDIALOG_H
