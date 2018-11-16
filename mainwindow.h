
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "borrowbookdlg.h"
#include"recorddialog.h"
#include"userdialog.h"
#include "returnbookdlg.h"

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

    void on_BtnPressManager_clicked();
    
    void on_BtnRecordManager_clicked();

    void on_BtnUserManager_clicked();

    void on_BtnReturn_clicked();
    
    void on_BtnBookManager_clicked();

private:
    Ui::MainWindow *ui;
    BorrowBookDlg *BkrDlg;
    RecordDialog *pRecordDlg;
    UserDialog *pUserDlg;
    ReturnBookDlg *pReturnDlg;
};

#endif // MAINWINDOW_H
