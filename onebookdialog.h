#ifndef ONEBOOKDIALOG_H
#define ONEBOOKDIALOG_H

#include <QDialog>

namespace Ui {
class OneBookDialog;
}

class OneBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OneBookDialog(QWidget *parent = nullptr);
    ~OneBookDialog();

private:
    Ui::OneBookDialog *ui;
};

#endif // ONEBOOKDIALOG_H
