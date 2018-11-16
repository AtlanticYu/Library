#ifndef USERUPDATEDIALOG_H
#define USERUPDATEDIALOG_H

#include <QDialog>
#include"dbManager.h"

namespace Ui {
class UserUpdateDialog;
}

class UserUpdateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserUpdateDialog(QWidget *parent = nullptr);
    ~UserUpdateDialog();
    QString USER_NAME;

private slots:
    void on_pushButton_Update_clicked();
    void getMessage(QString user_id,QString user_name,QString user_status);
    void on_pushButton_Close_clicked();

private:
    Ui::UserUpdateDialog *ui;


};

#endif // USERUPDATEDIALOG_H
