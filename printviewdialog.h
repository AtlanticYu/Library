#ifndef PRINTVIEWDIALOG_H
#define PRINTVIEWDIALOG_H

#include <QDialog>
#include<QPainter>
#include<QPrintDialog>
#include<QPrinter>
#include<QSqlQuery>

namespace Ui {
class printViewDialog;
}

class printViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit printViewDialog(QWidget *parent = nullptr);
    ~printViewDialog();

private:
    Ui::printViewDialog *ui;
private slots:
    void on_pushButton_Print_clicked();
    void getMessage(QString myHtml);

};

#endif // PRINTVIEWDIALOG_H
