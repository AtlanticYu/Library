#include "recorddialog.h"
#include "ui_recorddialog.h"



RecordDialog::RecordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecordDialog)
{
    ui->setupUi(this);
    mymodel=0;
    myOperationgStyle=0;//all
}

RecordDialog::~RecordDialog()
{
    delete ui;
}

void RecordDialog::on_pushButton_UserId_clicked()
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
        QMessageBox::information(this,"成功","连接数据库成功");
        QString user_id=ui->lineEdit_UserId->text();
        QString sql="select *from  T_RECORD where user_id="+user_id+";";
        QSqlQuery query(db);
        query.exec(sql);
        if(!query.next())
        {
           QMessageBox::information(this,"错误","不存在该ID用户的操作记录");
           return;
        }

            model= new QSqlTableModel(ui->tableView_record,db);
            model->setTable("T_RECORD");
            model->setEditStrategy(QSqlTableModel::OnManualSubmit);
            model->removeColumn(0);//不显示记录ID列
            model->setHeaderData(0,Qt::Horizontal,tr("用户ID"));
            model->setHeaderData(1,Qt::Horizontal,tr("用户名"));
            model->setHeaderData(2,Qt::Horizontal,tr("书ID"));
            model->setHeaderData(3,Qt::Horizontal,tr("书名"));
            model->setHeaderData(4,Qt::Horizontal,tr("操作类型"));
            model->setHeaderData(5,Qt::Horizontal,tr("操作时间"));
            model->setHeaderData(6,Qt::Horizontal,tr("罚款金额"));
            mymodel=1;

         model->setFilter(QObject::tr("user_id='%1'").arg(user_id));
         if(!model->select())
         {
            qDebug()<<"error"<<endl;
         }
         myOperationgStyle=1;
         ui->tableView_record->setModel(model);
         db.close();
         QSqlDatabase::removeDatabase("QSQLITE");
}

void RecordDialog::on_pushButton_BookId_clicked()
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
       //连接成功
       QMessageBox::information(this,"成功","连接数据库成功");
       QString book_id=ui->lineEdit_BookId->text();
       QString sql="select *from  T_RECORD where book_id="+book_id+";";
       QSqlQuery query(db);
       query.exec(sql);
       if(!query.next())
       {
          QMessageBox::information(this,"错误","不存在该ID书本的借阅记录");
          return;
       }

           model= new QSqlTableModel(ui->tableView_record,db);
           model->setTable("T_RECORD");
           model->setEditStrategy(QSqlTableModel::OnManualSubmit);
           model->removeColumn(0);//不显示记录ID列
           model->setHeaderData(0,Qt::Horizontal,tr("用户ID"));
           model->setHeaderData(1,Qt::Horizontal,tr("用户名"));
           model->setHeaderData(2,Qt::Horizontal,tr("书ID"));
           model->setHeaderData(3,Qt::Horizontal,tr("书名"));
           model->setHeaderData(4,Qt::Horizontal,tr("操作类型"));
           model->setHeaderData(5,Qt::Horizontal,tr("操作时间"));
           model->setHeaderData(6,Qt::Horizontal,tr("罚款金额"));
           mymodel=1;

        model->setFilter(QObject::tr("book_id='%1'").arg(book_id));
        if(!model->select())
        {
           qDebug()<<"error"<<endl;
        }
        myOperationgStyle=2;
        ui->tableView_record->setModel(model);
        db.close();
        QSqlDatabase::removeDatabase("QSQLITE");
}

void RecordDialog::on_pushButton_ShowAll_clicked()
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
    QMessageBox::information(this,"成功","连接数据库成功");

        model= new QSqlTableModel(ui->tableView_record,db);
        model->setTable("T_RECORD");
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->removeColumn(0);//不显示记录ID列
        model->setHeaderData(0,Qt::Horizontal,tr("用户ID"));
        model->setHeaderData(1,Qt::Horizontal,tr("用户名"));
        model->setHeaderData(2,Qt::Horizontal,tr("书ID"));
        model->setHeaderData(3,Qt::Horizontal,tr("书名"));
        model->setHeaderData(4,Qt::Horizontal,tr("操作类型"));
        model->setHeaderData(5,Qt::Horizontal,tr("操作时间"));
        model->setHeaderData(6,Qt::Horizontal,tr("罚款金额"));
        mymodel=1;
    if(!model->select())//select all record
    {
        QMessageBox::information(this,"error","数据库操作记录表格为空");
    }
    myOperationgStyle=0;
    ui->tableView_record->setModel(model);
    ui->tableView_record->show();
    db.close();
    QSqlDatabase::removeDatabase("QSQLITE");


}

int RecordDialog::getStatus()
{
    if(!ui->checkBox_borrow->isChecked() && !ui->checkBox_return->isChecked() && !ui->checkBox_fine->isChecked())
        return 0;
    if(ui->checkBox_borrow->isChecked() && !ui->checkBox_return->isChecked() && !ui->checkBox_fine->isChecked())
        return 1;
    if(!ui->checkBox_borrow->isChecked() && ui->checkBox_return->isChecked() && !ui->checkBox_fine->isChecked())
        return 2;
    if(!ui->checkBox_borrow->isChecked() && !ui->checkBox_return->isChecked() && ui->checkBox_fine->isChecked())
        return 3;

    if(ui->checkBox_borrow->isChecked() && ui->checkBox_return->isChecked() && !ui->checkBox_fine->isChecked())
        return 4;
    if(!ui->checkBox_borrow->isChecked() && ui->checkBox_return->isChecked() && ui->checkBox_fine->isChecked())
        return 5;
    if(ui->checkBox_borrow->isChecked() && !ui->checkBox_return->isChecked() && ui->checkBox_fine->isChecked())
        return 6;

    if(ui->checkBox_borrow->isChecked() && ui->checkBox_return->isChecked() && ui->checkBox_fine->isChecked())
        return 7;
}

//---------------------------------------------------all screen------------------------------------------
void  RecordDialog::screen1()
{
    model->setFilter(QObject::tr("operation_type='%1'").arg("借书"));
    if(!model->select())
    {
        QMessageBox::information(this,"error","查询所有借书记录失败");
    }
    ui->tableView_record->setModel(model);
    ui->tableView_record->show();

}
void  RecordDialog::screen2()
{
    model->setFilter(QObject::tr("operation_type='%1'").arg("还书"));
    if(!model->select())
    {
        QMessageBox::information(this,"error","查询所有还书记录失败");
    }
    ui->tableView_record->setModel(model);
    ui->tableView_record->show();

}
void  RecordDialog::screen3()
{
    model->setFilter(QObject::tr("operation_type='%1'").arg("超期罚款"));
    if(!model->select())
    {
        QMessageBox::information(this,"error","查询所有超期罚款记录失败");
    }
    ui->tableView_record->setModel(model);
    ui->tableView_record->show();
}
void  RecordDialog::screen4()
{
    model->setFilter(QObject::tr("operation_type='%1' or operation_type='%2'").arg("借书").arg("还书"));
    if(!model->select())
    {
        QMessageBox::information(this,"error","查询所有借书,还书记录失败");
    }
    ui->tableView_record->setModel(model);
    ui->tableView_record->show();
}
void  RecordDialog::screen5()
{
    model->setFilter(QObject::tr("operation_type='%1' or operation_type='%2'").arg("超期罚款").arg("还书"));
    if(!model->select())
    {
        QMessageBox::information(this,"error","查询所有超期罚款,还书记录失败");
    }
    ui->tableView_record->setModel(model);
    ui->tableView_record->show();
}
void  RecordDialog::screen6()
{
    model->setFilter(QObject::tr("operation_type='%1' or operation_type='%2'").arg("超期罚款").arg("借书"));
    if(!model->select())
    {
        QMessageBox::information(this,"error","查询所有超期罚款,借书记录失败");
    }
    ui->tableView_record->setModel(model);
    ui->tableView_record->show();
}
void  RecordDialog::screen7()
{
    model->setFilter(QObject::tr("operation_type='%1' or operation_type='%2' or operation_type='%3'").arg("超期罚款").arg("借书").arg("还书"));
    if(!model->select())
     {
         QMessageBox::information(this,"error","筛选所有类型的操作记录,失败");
     }
     ui->tableView_record->setModel(model);
     ui->tableView_record->show();
    QMessageBox::information(this,"ok","筛选所有类型的操作记录,成功");

}

//----------------------------------------------------user screen-------------------------------------------
void RecordDialog:: screen11()
{
    QModelIndex index = model->index(0,0);//取得user_id
    QString user_id=index.data().toString();
    model->setFilter(QObject::tr("user_id='%1' and operation_type='%2'").arg(user_id).arg("借书"));
    if(!model->select())
    {
        QMessageBox::information(this,"error","查询用户借书记录失败");
    }
    ui->tableView_record->setModel(model);
    ui->tableView_record->show();

}
void RecordDialog:: screen22()
{
    QModelIndex index = model->index(0,0);//取得user_id
    QString user_id=index.data().toString();
    model->setFilter(QObject::tr("user_id='%1' and operation_type='%2'").arg(user_id).arg("还书"));
    if(!model->select())
    {
        QMessageBox::information(this,"error","查询用户还书记录失败");
    }
    ui->tableView_record->setModel(model);
    ui->tableView_record->show();
}
void RecordDialog:: screen33()
{
    QModelIndex index = model->index(0,0);//取得user_id
    QString user_id=index.data().toString();
    model->setFilter(QObject::tr("user_id='%1' and operation_type='%2'").arg(user_id).arg("超期罚款"));
    if(!model->select())
    {
        QMessageBox::information(this,"error","查询用户超期罚款记录失败");
    }
    ui->tableView_record->setModel(model);
    ui->tableView_record->show();

}
void RecordDialog:: screen44()
{
    QModelIndex index = model->index(0,0);//取得user_id
    QString user_id=index.data().toString();
    model->setFilter(QObject::tr("user_id='%1' and operation_type='%2' or user_id='%1' and operation_type='%3'").arg(user_id).arg("还书").arg("借书"));
    if(!model->select())
    {
        QMessageBox::information(this,"error","查询用户还书,借书记录失败");
    }
    ui->tableView_record->setModel(model);
    ui->tableView_record->show();
}
void RecordDialog:: screen55()
{
    QModelIndex index = model->index(0,0);//取得user_id
    QString user_id=index.data().toString();
    model->setFilter(QObject::tr("user_id='%1' and operation_type='%2' or user_id='%1' and operation_type='%3'").arg(user_id).arg("还书").arg("超期罚款"));
    if(!model->select())
    {
        QMessageBox::information(this,"error","查询用户超期罚款,还书记录失败");
    }
    ui->tableView_record->setModel(model);
    ui->tableView_record->show();

}
void RecordDialog:: screen66()
{
    QModelIndex index = model->index(0,0);//取得user_id
    QString user_id=index.data().toString();
    model->setFilter(QObject::tr("user_id='%1' and operation_type='%2' or user_id='%1' and operation_type='%3'").arg(user_id).arg("借书").arg("超期罚款"));
    if(!model->select())
    {
        QMessageBox::information(this,"error","查询用户超期罚款,借书记录失败");
    }
    ui->tableView_record->setModel(model);
    ui->tableView_record->show();

}
void RecordDialog:: screen77()
{
    QModelIndex index = model->index(0,0);//取得user_id
    QString user_id=index.data().toString();
    model->setFilter(QObject::tr("user_id='%1'").arg(user_id));
    if(!model->select())
    {
        QMessageBox::information(this,"error","筛选用户,所有类型的操作记录,失败");
    }
    ui->tableView_record->setModel(model);
    ui->tableView_record->show();
    QMessageBox::information(this,"ok","筛选用户,所有类型的操作记录成功");
}

//----------------------------------------------------book screen-----------------------------------------------
void RecordDialog:: screen111()
{
    QModelIndex index = model->index(0,2);//取得book_id
    QString book_id=index.data().toString();
    model->setFilter(QObject::tr("book_id='%1' and operation_type='%2'").arg(book_id).arg("借书"));
    if(!model->select())
    {
        QMessageBox::information(this,"error","查询图书借书记录失败");
    }
    ui->tableView_record->setModel(model);
    ui->tableView_record->show();

}
void RecordDialog:: screen222()
{
    QModelIndex index = model->index(0,2);//取得book_id
    QString book_id=index.data().toString();
    model->setFilter(QObject::tr("book_id='%1' and operation_type='%2'").arg(book_id).arg("还书"));
    if(!model->select())
    {
        QMessageBox::information(this,"error","查询图书还书记录失败");
    }
    ui->tableView_record->setModel(model);
    ui->tableView_record->show();
}
void RecordDialog:: screen333()
{
    QModelIndex index = model->index(0,2);//取得book_id
    QString book_id=index.data().toString();
    model->setFilter(QObject::tr("book_id='%1' and operation_type='%2'").arg(book_id).arg("超期罚款"));
    if(!model->select())
    {
        QMessageBox::information(this,"error","查询图书超期罚款记录失败");
    }
    ui->tableView_record->setModel(model);
    ui->tableView_record->show();

}
void RecordDialog:: screen444()
{
    QModelIndex index = model->index(0,2);//取得book_id
    QString book_id=index.data().toString();
    model->setFilter(QObject::tr("book_id='%1' and operation_type='%2' or book_id='%1' and operation_type='%3'").arg(book_id).arg("还书").arg("借书"));
    if(!model->select())
    {
        QMessageBox::information(this,"error","查询图书还书,借书记录失败");
    }
    ui->tableView_record->setModel(model);
    ui->tableView_record->show();
}
void RecordDialog:: screen555()
{
    QModelIndex index = model->index(0,2);//取得book_id
    QString book_id=index.data().toString();
    model->setFilter(QObject::tr("book_id='%1' and operation_type='%2' or book_id='%1' and operation_type='%3'").arg(book_id).arg("还书").arg("超期罚款"));
    if(!model->select())
    {
        QMessageBox::information(this,"error","查询图书超期罚款,还书记录失败");
    }
    ui->tableView_record->setModel(model);
    ui->tableView_record->show();

}
void RecordDialog:: screen666()
{
    QModelIndex index = model->index(0,2);//取得book_id
    QString book_id=index.data().toString();
    model->setFilter(QObject::tr("book_id='%1' and operation_type='%2' or book_id='%1' and operation_type='%3'").arg(book_id).arg("借书").arg("超期罚款"));
    if(!model->select())
    {
        QMessageBox::information(this,"error","查询图书超期罚款,借书记录失败");
    }
    ui->tableView_record->setModel(model);
    ui->tableView_record->show();

}
void RecordDialog:: screen777()
{
    QModelIndex index = model->index(0,2);//取得book_id
    QString book_id=index.data().toString();
    model->setFilter(QObject::tr("book_id='%1'").arg(book_id));
    if(!model->select())
    {
        QMessageBox::information(this,"error","筛选图书,所有类型的操作记录,失败");
    }
    ui->tableView_record->setModel(model);
    ui->tableView_record->show();
    QMessageBox::information(this,"ok","筛选图书,所有类型的操作记录,成功");
}





void RecordDialog::on_pushButton_screen_clicked()
{
    if(mymodel==0)
    {
        QMessageBox::information(this,"错误","表格记录为空，筛选失败.");
        return;
    }
    if(ui->tableView_record->model()->rowCount()==0)
    {
        QMessageBox::information(this,"错误","表格记录为空，筛选失败.");
        return;
    }
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
    QMessageBox::information(this,"成功","连接数据库成功");
    if(myOperationgStyle==0)//all
    {
        int status=getStatus();
        switch (status)
        {
            case 0:QMessageBox::information(this,"ok","您并未勾选筛选条件");break;
            case 1:screen1();break;
            case 2:screen2();break;
            case 3:screen3();break;
            case 4:screen4();break;
            case 5:screen5();break;
            case 6:screen6();break;
            case 7:screen7();break;
            default:QMessageBox::information(this,"error","筛选失败，出现异常");break;
        }

    }
    if(myOperationgStyle==1)//user
    {
        int status=getStatus();
        switch (status)
        {
            case 0:QMessageBox::information(this,"ok","您并未勾选筛选条件");break;
            case 1:screen11();break;
            case 2:screen22();break;
            case 3:screen33();break;
            case 4:screen44();break;
            case 5:screen55();break;
            case 6:screen66();break;
            case 7:screen77();break;
            default:QMessageBox::information(this,"error","筛选失败，出现异常");break;
        }

    }
    if(myOperationgStyle==2)//book
    {
        int status=getStatus();
        switch (status)
        {
            case 0:QMessageBox::information(this,"ok","您并未勾选筛选条件");break;
            case 1:screen111();break;
            case 2:screen222();break;
            case 3:screen333();break;
            case 4:screen444();break;
            case 5:screen555();break;
            case 6:screen666();break;
            case 7:screen777();break;
            default:QMessageBox::information(this,"error","筛选失败，出现异常");break;
        }

    }
    db.close();
    QSqlDatabase::removeDatabase("QSQLITE");


}



void RecordDialog::on_pushButton_ShowPdf_clicked()
{
    if(mymodel==0)
    {
        QMessageBox::information(this,"错误","表格记录为空，查看预览失败.");
        return;
    }
    if(ui->tableView_record->model()->rowCount()==0)
    {
        QMessageBox::information(this,"错误","表格记录为空，查看预览失败.");
        return;
    }
    int column = model->columnCount(); //获得列数
    int row = model->rowCount();    // 获得行数
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
            QModelIndex index = model->index(0,0);//取得user_id
            QString user_id=index.data().toString();
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
          QModelIndex index = model->index(0,2);//取得book_id
          QString book_id=index.data().toString();
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
              QModelIndex index = model->index(i,j);//依次取得所有单元格的值
              QString date=index.data().toString();
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
