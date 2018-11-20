#include "recorddialog.h"
#include "ui_recorddialog.h"
#include"dbManager.h"



RecordDialog::RecordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecordDialog)
{
    ui->setupUi(this);
    myOperationgStyle=0;//all
}

RecordDialog::~RecordDialog()
{
    delete ui;
}

void RecordDialog::on_pushButton_UserId_clicked()
{
    //clear table
    myOperationgStyle=1;
    while(ui->tableWidget->rowCount()!=0)
    {
        ui->tableWidget->removeRow(0);
    }
    QString user_id=ui->lineEdit_UserId->text();
    if (""==user_id)
    {
         QMessageBox::information(this,"error","用户ID为空，请您先输入用户ID。");
         return;
    }
    //连接数据库
    dbManager dbmanager;
    dbmanager.setDBMessage("QSQLITE","./MyLibrary.db","myconnection");
    QSqlDatabase db=dbmanager.getDB();
    //连接失败
    if (!db.open())
    {
        QMessageBox::information(this,"失败","连接数据库失败.");
        return;
    }
    //连接成功
    QMessageBox::information(this,"成功","连接数据库成功");
    QString sql="select *from  T_RECORD where user_id="+user_id+";";
    QSqlQuery query(db);
    if(!query.exec(sql))
    {
        QMessageBox::information(this,"查询失败","败查询指定用户的借阅记录失败");
        return;
    }
    if(!query.next())
    {
        QMessageBox::information(this,"error","不存在该用户的操作记录");
        return;
    }
    else
    {
        ui->tableWidget->insertRow(0);
        QTableWidgetItem *p0=new QTableWidgetItem(query.value(1).toString());
        QTableWidgetItem *p1=new QTableWidgetItem(query.value(2).toString());
        QTableWidgetItem *p2=new QTableWidgetItem(query.value(3).toString());
        QTableWidgetItem *p3=new QTableWidgetItem(query.value(4).toString());
        QTableWidgetItem *p4=new QTableWidgetItem(query.value(5).toString());
        QTableWidgetItem *p5=new QTableWidgetItem(query.value(6).toString());
        QTableWidgetItem *p6=new QTableWidgetItem(query.value(7).toString());
        ui->tableWidget->setItem(0,0,p0);
        ui->tableWidget->setItem(0,1,p1);
        ui->tableWidget->setItem(0,2,p2);
        ui->tableWidget->setItem(0,3,p3);
        ui->tableWidget->setItem(0,4,p4);
        ui->tableWidget->setItem(0,5,p5);
        ui->tableWidget->setItem(0,6,p6);
        while(query.next())
        {
            ui->tableWidget->insertRow(0);
            QTableWidgetItem *p0=new QTableWidgetItem(query.value(1).toString());
            QTableWidgetItem *p1=new QTableWidgetItem(query.value(2).toString());
            QTableWidgetItem *p2=new QTableWidgetItem(query.value(3).toString());
            QTableWidgetItem *p3=new QTableWidgetItem(query.value(4).toString());
            QTableWidgetItem *p4=new QTableWidgetItem(query.value(5).toString());
            QTableWidgetItem *p5=new QTableWidgetItem(query.value(6).toString());
            QTableWidgetItem *p6=new QTableWidgetItem(query.value(7).toString());
            ui->tableWidget->setItem(0,0,p0);
            ui->tableWidget->setItem(0,1,p1);
            ui->tableWidget->setItem(0,2,p2);
            ui->tableWidget->setItem(0,3,p3);
            ui->tableWidget->setItem(0,4,p4);
            ui->tableWidget->setItem(0,5,p5);
            ui->tableWidget->setItem(0,6,p6);
        }
    }


}

void RecordDialog::on_pushButton_BookId_clicked()
{
    //clear table
    myOperationgStyle=2;
    while(ui->tableWidget->rowCount()!=0)
    {
        ui->tableWidget->removeRow(0);
    }
    QString book_id=ui->lineEdit_BookId->text();
    if (""==book_id)
    {
         QMessageBox::information(this,"error","书本ID为空，请您先输入书本ID。");
         return;
    }
    //连接数据库
    dbManager dbmanager;
    dbmanager.setDBMessage("QSQLITE","./MyLibrary.db","myconnection");
    QSqlDatabase db=dbmanager.getDB();
    //连接失败
    if (!db.open())
    {
        QMessageBox::information(this,"失败","连接数据库失败.");
        return;
    }
    //连接成功
    QMessageBox::information(this,"成功","连接数据库成功");
    QString sql="select *from  T_RECORD where book_id="+book_id+";";
    QSqlQuery query(db);
    if(!query.exec(sql))
    {
        QMessageBox::information(this,"查询失败","查询指定书本的借阅记录失败");
        return;
    }
    if(!query.next())
    {
        QMessageBox::information(this,"error","不存在该书本的操作记录");
        return;
    }
    else
    {
        ui->tableWidget->insertRow(0);
        QTableWidgetItem *p0=new QTableWidgetItem(query.value(1).toString());
        QTableWidgetItem *p1=new QTableWidgetItem(query.value(2).toString());
        QTableWidgetItem *p2=new QTableWidgetItem(query.value(3).toString());
        QTableWidgetItem *p3=new QTableWidgetItem(query.value(4).toString());
        QTableWidgetItem *p4=new QTableWidgetItem(query.value(5).toString());
        QTableWidgetItem *p5=new QTableWidgetItem(query.value(6).toString());
        QTableWidgetItem *p6=new QTableWidgetItem(query.value(7).toString());
        ui->tableWidget->setItem(0,0,p0);
        ui->tableWidget->setItem(0,1,p1);
        ui->tableWidget->setItem(0,2,p2);
        ui->tableWidget->setItem(0,3,p3);
        ui->tableWidget->setItem(0,4,p4);
        ui->tableWidget->setItem(0,5,p5);
        ui->tableWidget->setItem(0,6,p6);
        while(query.next())
        {
            ui->tableWidget->insertRow(0);
            QTableWidgetItem *p0=new QTableWidgetItem(query.value(1).toString());
            QTableWidgetItem *p1=new QTableWidgetItem(query.value(2).toString());
            QTableWidgetItem *p2=new QTableWidgetItem(query.value(3).toString());
            QTableWidgetItem *p3=new QTableWidgetItem(query.value(4).toString());
            QTableWidgetItem *p4=new QTableWidgetItem(query.value(5).toString());
            QTableWidgetItem *p5=new QTableWidgetItem(query.value(6).toString());
            QTableWidgetItem *p6=new QTableWidgetItem(query.value(7).toString());
            ui->tableWidget->setItem(0,0,p0);
            ui->tableWidget->setItem(0,1,p1);
            ui->tableWidget->setItem(0,2,p2);
            ui->tableWidget->setItem(0,3,p3);
            ui->tableWidget->setItem(0,4,p4);
            ui->tableWidget->setItem(0,5,p5);
            ui->tableWidget->setItem(0,6,p6);
        }
    }



}

void RecordDialog::on_pushButton_ShowAll_clicked()
{
    //clear table
    myOperationgStyle=0;
    while(ui->tableWidget->rowCount()!=0)
    {
        ui->tableWidget->removeRow(0);
    }
    //连接数据库
    dbManager dbmanager;
    dbmanager.setDBMessage("QSQLITE","./MyLibrary.db","myconnection");
    QSqlDatabase db=dbmanager.getDB();
    //连接失败
    if (!db.open())
    {
        QMessageBox::information(this,"失败","连接数据库失败.");
        return;
    }
    QMessageBox::information(this,"成功","连接数据库成功");
    QString sql="select * from T_RECORD";
    QSqlQuery query(db);
    if(!query.exec(sql))
    {
        QMessageBox::information(this,"error","查询操作记录表格失败");
        return;
    }
    if(!query.next())
    {
        QMessageBox::information(this,"error","数据库操作记录表格为空");
        return;
    }
    else
    {
        ui->tableWidget->insertRow(0);
        QTableWidgetItem *p0=new QTableWidgetItem(query.value(1).toString());
        QTableWidgetItem *p1=new QTableWidgetItem(query.value(2).toString());
        QTableWidgetItem *p2=new QTableWidgetItem(query.value(3).toString());
        QTableWidgetItem *p3=new QTableWidgetItem(query.value(4).toString());
        QTableWidgetItem *p4=new QTableWidgetItem(query.value(5).toString());
        QTableWidgetItem *p5=new QTableWidgetItem(query.value(6).toString());
        QTableWidgetItem *p6=new QTableWidgetItem(query.value(7).toString());
        ui->tableWidget->setItem(0,0,p0);
        ui->tableWidget->setItem(0,1,p1);
        ui->tableWidget->setItem(0,2,p2);
        ui->tableWidget->setItem(0,3,p3);
        ui->tableWidget->setItem(0,4,p4);
        ui->tableWidget->setItem(0,5,p5);
        ui->tableWidget->setItem(0,6,p6);
        while(query.next())
        {
            ui->tableWidget->insertRow(0);
            QTableWidgetItem *p0=new QTableWidgetItem(query.value(1).toString());
            QTableWidgetItem *p1=new QTableWidgetItem(query.value(2).toString());
            QTableWidgetItem *p2=new QTableWidgetItem(query.value(3).toString());
            QTableWidgetItem *p3=new QTableWidgetItem(query.value(4).toString());
            QTableWidgetItem *p4=new QTableWidgetItem(query.value(5).toString());
            QTableWidgetItem *p5=new QTableWidgetItem(query.value(6).toString());
            QTableWidgetItem *p6=new QTableWidgetItem(query.value(7).toString());
            ui->tableWidget->setItem(0,0,p0);
            ui->tableWidget->setItem(0,1,p1);
            ui->tableWidget->setItem(0,2,p2);
            ui->tableWidget->setItem(0,3,p3);
            ui->tableWidget->setItem(0,4,p4);
            ui->tableWidget->setItem(0,5,p5);
            ui->tableWidget->setItem(0,6,p6);
        }
    }
    db.close();
    QSqlDatabase::removeDatabase("QSQLITE");

}

int RecordDialog::getStatus()
{
    if(!ui->checkBox_borrow->isChecked() && !ui->checkBox_return->isChecked() &&   !ui->checkBox_lost->isChecked() && !ui->checkBox_fine->isChecked())
        return 0;
    if(!ui->checkBox_borrow->isChecked() && !ui->checkBox_return->isChecked() &&   !ui->checkBox_lost->isChecked() && ui->checkBox_fine->isChecked())
        return 1;
    if(!ui->checkBox_borrow->isChecked() && !ui->checkBox_return->isChecked() &&   ui->checkBox_lost->isChecked() && !ui->checkBox_fine->isChecked())
        return 2;
    if(!ui->checkBox_borrow->isChecked() && !ui->checkBox_return->isChecked() &&   ui->checkBox_lost->isChecked() && ui->checkBox_fine->isChecked())
        return 3;
    if(!ui->checkBox_borrow->isChecked() && ui->checkBox_return->isChecked() &&   !ui->checkBox_lost->isChecked() && !ui->checkBox_fine->isChecked())
        return 4;
    if(!ui->checkBox_borrow->isChecked() && ui->checkBox_return->isChecked() &&   !ui->checkBox_lost->isChecked() && ui->checkBox_fine->isChecked())
        return 5;
    if(!ui->checkBox_borrow->isChecked() && ui->checkBox_return->isChecked() &&   ui->checkBox_lost->isChecked() && !ui->checkBox_fine->isChecked())
        return 6;
    if(!ui->checkBox_borrow->isChecked() && ui->checkBox_return->isChecked() &&   ui->checkBox_lost->isChecked() && ui->checkBox_fine->isChecked())
        return 7;
    if(ui->checkBox_borrow->isChecked() && !ui->checkBox_return->isChecked() &&   !ui->checkBox_lost->isChecked() && !ui->checkBox_fine->isChecked())
        return 8;
    if(ui->checkBox_borrow->isChecked() && !ui->checkBox_return->isChecked() &&   !ui->checkBox_lost->isChecked() && ui->checkBox_fine->isChecked())
        return 9;
    if(ui->checkBox_borrow->isChecked() && !ui->checkBox_return->isChecked() &&   ui->checkBox_lost->isChecked() && !ui->checkBox_fine->isChecked())
        return 10;
    if(ui->checkBox_borrow->isChecked() && !ui->checkBox_return->isChecked() &&   ui->checkBox_lost->isChecked() && ui->checkBox_fine->isChecked())
        return 11;
    if(ui->checkBox_borrow->isChecked() && ui->checkBox_return->isChecked() &&   !ui->checkBox_lost->isChecked() && !ui->checkBox_fine->isChecked())
        return 12;
    if(ui->checkBox_borrow->isChecked() && ui->checkBox_return->isChecked() &&   !ui->checkBox_lost->isChecked() && ui->checkBox_fine->isChecked())
        return 13;
    if(ui->checkBox_borrow->isChecked() && ui->checkBox_return->isChecked() &&   ui->checkBox_lost->isChecked() && !ui->checkBox_fine->isChecked())
        return 14;
    if(ui->checkBox_borrow->isChecked() && ui->checkBox_return->isChecked() &&   ui->checkBox_lost->isChecked() && ui->checkBox_fine->isChecked())
        return 15;
}


void  RecordDialog::screen1()
{
    for(int i=0;i<ui->tableWidget->rowCount();)
    {
        QString operationg_style=ui->tableWidget->item(i,4)->text();
        if(operationg_style!="超期罚款")
            ui->tableWidget->removeRow(i);
        else
            i++;
    }

}
void  RecordDialog::screen2()
{
    for(int i=0;i<ui->tableWidget->rowCount();)
    {
        QString operationg_style=ui->tableWidget->item(i,4)->text();
        if(operationg_style!="丢书")
            ui->tableWidget->removeRow(i);
        else
            i++;
    }

}
void  RecordDialog::screen3()
{
    for(int i=0;i<ui->tableWidget->rowCount();)
    {
        QString operationg_style=ui->tableWidget->item(i,4)->text();
        if(operationg_style!="丢书" && operationg_style!="超期罚款")
            ui->tableWidget->removeRow(i);
        else
            i++;
    }

}
void  RecordDialog::screen4()
{
    for(int i=0;i<ui->tableWidget->rowCount();)
    {
        QString operationg_style=ui->tableWidget->item(i,4)->text();
        if(operationg_style!="还书")
            ui->tableWidget->removeRow(i);
        else
            i++;
    }

}
void  RecordDialog::screen5()
{
    for(int i=0;i<ui->tableWidget->rowCount();)
    {
        QString operationg_style=ui->tableWidget->item(i,4)->text();
        if(operationg_style!="还书" && operationg_style!="超期罚款")
            ui->tableWidget->removeRow(i);
        else
            i++;
    }

}
void  RecordDialog::screen6()
{
    for(int i=0;i<ui->tableWidget->rowCount();)
    {
        QString operationg_style=ui->tableWidget->item(i,4)->text();
        if(operationg_style!="还书" && operationg_style!="丢书")
            ui->tableWidget->removeRow(i);
        else
            i++;
    }

}
void  RecordDialog::screen7()
{
    for(int i=0;i<ui->tableWidget->rowCount();)
    {
        QString operationg_style=ui->tableWidget->item(i,4)->text();
        if(operationg_style=="借书")
            ui->tableWidget->removeRow(i);
        else
            i++;
    }

}
void RecordDialog::screen8()
{
    for(int i=0;i<ui->tableWidget->rowCount();)
    {
        QString operationg_style=ui->tableWidget->item(i,4)->text();
        if(operationg_style!="借书")
            ui->tableWidget->removeRow(i);
        else
            i++;
    }
}
void RecordDialog:: screen9()
{
    for(int i=0;i<ui->tableWidget->rowCount();)
    {
        QString operationg_style=ui->tableWidget->item(i,4)->text();
        if(operationg_style!="借书" && operationg_style!="超期罚款")
            ui->tableWidget->removeRow(i);
        else
            i++;
    }
}
void RecordDialog:: screen10()
{
    for(int i=0;i<ui->tableWidget->rowCount();)
    {
        QString operationg_style=ui->tableWidget->item(i,4)->text();
        if(operationg_style!="借书" && operationg_style!="丢书")
            ui->tableWidget->removeRow(i);
        else
            i++;
    }
}
void RecordDialog:: screen11()
{
    for(int i=0;i<ui->tableWidget->rowCount();)
    {
        QString operationg_style=ui->tableWidget->item(i,4)->text();
        if(operationg_style=="还书")
            ui->tableWidget->removeRow(i);
        else
            i++;
    }
}
void RecordDialog:: screen12()
{
    for(int i=0;i<ui->tableWidget->rowCount();)
    {
        QString operationg_style=ui->tableWidget->item(i,4)->text();
        if(operationg_style!="借书" && operationg_style!="还书")
            ui->tableWidget->removeRow(i);
        else
            i++;
    }
}
void RecordDialog:: screen13()
{
    for(int i=0;i<ui->tableWidget->rowCount();)
    {
        QString operationg_style=ui->tableWidget->item(i,4)->text();
        if(operationg_style=="丢书")
            ui->tableWidget->removeRow(i);
        else
            i++;
    }
}
void RecordDialog::  screen14()
{
    for(int i=0;i<ui->tableWidget->rowCount();)
    {
        QString operationg_style=ui->tableWidget->item(i,4)->text();
        if(operationg_style=="超期罚款")
            ui->tableWidget->removeRow(i);
        else
            i++;
    }
}
void RecordDialog::  screen15()
{
    QMessageBox::information(this,"OK","显示所有类型,筛选仅针对表格内容哦，亲。");
}


void RecordDialog::on_pushButton_screen_clicked()
{
    if(ui->tableWidget->rowCount()<=0)
    {
        QMessageBox::information(this,"错误","表格记录为空， 筛选失败.");
        return;
    }
    int status=getStatus();
    switch (status)
    {
    case 0:QMessageBox::information(this,"ok","您并未勾选任何筛选条件.");break;
    case 1:screen1();break;
    case 2:screen2();break;
    case 3:screen3();break;
    case 4:screen4();break;
    case 5:screen5();break;
    case 6:screen6();break;
    case 7:screen7();break;
    case 8:screen8();break;
    case 9:screen9();break;
    case 10:screen10();break;
    case 11:screen11();break;
    case 12:screen12();break;
    case 13:screen13();break;
    case 14:screen14();break;
    case 15:screen15();break;
    default:QMessageBox::information(this,"error","筛选错误.");break;
    }

}



void RecordDialog::on_pushButton_ShowPdf_clicked()
{
    if(ui->tableWidget->rowCount()<=0)
    {
        QMessageBox::information(this,"错误","表格记录为空，查看预览失败.");
        return;
    }
    //连接数据库
    dbManager dbmanager;
    dbmanager.setDBMessage("QSQLITE","./MyLibrary.db","myconnection");
    QSqlDatabase db=dbmanager.getDB();
    //连接失败
    if (!db.open())
    {
        QMessageBox::information(this,"失败","连接数据库失败.");
        return;
    }
    QMessageBox::information(this,"成功","连接数据库成功");
    int column =7; //获得列数
    int row = ui->tableWidget->rowCount();    // 获得行数
    QString myHtml;
    if(0==myOperationgStyle)//all
        myHtml="<h1 style=text-align:center>全部借阅记录如下：</h1>";
    else
    {
        //连接数据库
        if (QSqlDatabase::contains("myconn"))
        {
           db = QSqlDatabase::database("myconn");
        }
        else
        {
           db = QSqlDatabase::addDatabase("QSQLITE", "myconn");//加载数据库驱动，并命名连接名称为myconn
        }
        db.setDatabaseName("./MyLibrary.db");
        //连接失败
        if (!db.open())
        {
            QMessageBox::information(this,"失败","连接数据库失败.");
            return;
        }

       if(1==myOperationgStyle)//user
       {
            QString user_id=ui->tableWidget->item(0,0)->text();
            QSqlQuery query(db);
            QString sql="select * from T_USER where user_id="+user_id+";";
            query.exec(sql);
            while(query.next())
            {
                QString userid=query.value(0).toString();
                QString user_name=query.value(1).toString();
                QString user_status=query.value(2).toString();
                myHtml="<h1 style=text-align:center>用户借阅记录如下：</h1><h4>用户ID:"+userid+"</h4><h4>用户名:"+user_name+"</h4><h4>用户身份:"+user_status+"</h4>";
            }
      }

      if(2==myOperationgStyle)//book
      {
          QString book_id=ui->tableWidget->item(0,2)->text();//取得book_id
          QSqlQuery query(db);
          QString sql="select * from T_BOOK where book_id="+book_id+";";
          query.exec(sql);
          while(query.next())
          {
              QString bookid=query.value(0).toString();
              QString book_name=query.value(1).toString();
              QString press_id=query.value(2).toString();
              QString press_name=query.value(3).toString();
              QString press_time=query.value(4).toString();
              myHtml="<h1 style=text-align:center>指定图书借阅记录如下：</h1><h4>图书ID:"+bookid+"</h4><h4>图书名:"+book_name+"</h4><h4>出版社ID :"+press_id+"</h4><h4>出版社名称:"+press_name+"</h4><h4>出版时间:"+press_time+"</h4>";
          }

      }
      db.close();
      QSqlDatabase::removeDatabase("QSQLITE");
    }
    myHtml=myHtml+"<table border='1' cellspacing='0'><tr><th>用户ID</th><th>用户名</th><th>书ID</th><th>书名</th><th>操作类型</th><th>操作时间</th><th>罚款金额</th></tr>";
    for(int i=0;i<row;i++)
    {
        myHtml=myHtml+"<tr>";
        for(int j=0;j<column;j++)
        {
              //依次取得所有单元格的值
              QString date=ui->tableWidget->item(i,j)->text();
              myHtml=myHtml+"<td>"+date+"</td>";
             // qDebug()<<"test:"<<index.data()<<endl;
        }
        myHtml=myHtml+"</tr>";
    }
    myHtml=myHtml+"</table>";
    printViewDialog *pPrintViewDlg = new printViewDialog(this);
    pPrintViewDlg->setModal(false);
    connect(this,SIGNAL(sendMyHtml(QString)),pPrintViewDlg,SLOT(getMessage(QString)));//声明槽的映射关系
    emit sendMyHtml(myHtml);
    pPrintViewDlg->show();

}
