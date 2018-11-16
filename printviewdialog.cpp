#include "printviewdialog.h"
#include "ui_printviewdialog.h"


printViewDialog::printViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::printViewDialog)
{
    ui->setupUi(this);
//    QString html;
//    html="<h1>吴汶斌是大傻逼</h1>";
//    ui->textEdit->setHtml(html);
}

printViewDialog::~printViewDialog()
{
    delete ui;
}

void printViewDialog:: getMessage(QString myHtml)
{
    ui->textEdit->setHtml(myHtml);
}

void printViewDialog::on_pushButton_Print_clicked()
{
    QPrintDialog printerDlg(this);
    printerDlg.setWindowTitle("打印");
    if(printerDlg.exec()== QPrintDialog::Accepted )
    {
        QPrinter* printer=printerDlg.printer();//创建打印机对象指针，并获得打印对话框的操作后的打印属性。
        ui->textEdit->print(printer);//打印edt对话框当中的信息
    }
}


