#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "borrowbookdlg.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_BtnBorrow_clicked();

private:
    Ui::MainWindow *ui;
    BorrowBookDlg *BkrDlg;
};

#endif // MAINWINDOW_H
