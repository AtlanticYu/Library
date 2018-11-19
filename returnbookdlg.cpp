#include "returnbookdlg.h"
#include "ui_returnbookdlg.h"
#include <QDateTime>
ReturnBookDlg::ReturnBookDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReturnBookDlg)
{
    ui->setupUi(this);
}

ReturnBookDlg::~ReturnBookDlg()
{
    delete ui;
}

void ReturnBookDlg::on_BtnSelect_clicked()
{
    model= new QSqlQueryModel(ui->viewrecord);
    mymodel=1;
    ui->viewrecord->setModel(model);
    QSqlDatabase db;
    if (QSqlDatabase::contains("myconn")){
        db = QSqlDatabase::database("myconn");
    }
    else{
        db = QSqlDatabase::addDatabase("QSQLITE", "myconn");//加载数据库驱动
    }
    db.setDatabaseName("./MyLibrary.db");  //数据库名称
    if (!db.open()){
        QMessageBox::information(this,"失败","连接数据库失败.");
        return;
    }
    else{
        QString userid=ui->Edtuser->text();
        QString bookid=ui->Edtbook->text();
        QString sql="select *from  T_RECORD where user_id="+userid+" and book_id="+bookid+";";
        QSqlQuery query(db);
        query.exec(sql);
        if(!query.next()){
            QMessageBox::information(this,"警告","不存在的操作记录");
            return;
        }
        else{
            model->setQuery(sql,db);
            model->removeColumn(0);//不显示记录ID列
            model->setHeaderData(0,Qt::Horizontal,tr("用户ID"));
            model->setHeaderData(1,Qt::Horizontal,tr("用户名"));
            model->setHeaderData(2,Qt::Horizontal,tr("书ID"));
            model->setHeaderData(3,Qt::Horizontal,tr("书名"));
            model->setHeaderData(4,Qt::Horizontal,tr("操作类型"));
            model->setHeaderData(5,Qt::Horizontal,tr("操作时间"));
            model->setHeaderData(6,Qt::Horizontal,tr("罚款金额"));
            ui->viewrecord->setModel(model);
            ui->viewrecord->resizeColumnsToContents();
        }
        db.close();
        QSqlDatabase::removeDatabase("QSQLITE");
    }
}

void ReturnBookDlg::on_BtnReturn_clicked()
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("myconn")){
        db=QSqlDatabase::database("myconn");
    }
    else{
        db=QSqlDatabase::addDatabase("QSQLITE","myconn");
    }
    db.setDatabaseName("./MyLibrary.db");
    if(!db.open()){
        QMessageBox::information(this,"警告","数据库打开失败");
        return;
    }
    QString usrid=ui->Edtuser->text();    //用户ID
    QString bookid=ui->Edtbook->text();       //书ID
    QString sql0="select * from T_RECORD where user_id="+usrid+" and book_id="+bookid+" and operation_type='借书' order by operation_time desc;";
    QSqlQuery query(db);
    query.exec(sql0);
    if(!query.next()){
        QMessageBox::information(this,"警告","sql0执行失败");
        return;
    }
    QString starttime=query.value(6).toString();
    /*sqlite3_get_table(pDb,sql0.toStdString().c_str(),&Result,&row,&col,&errmsg);
   // char *tim=Result[(row+1)*col-2];
    //QString starttime;         //借书时间
    while (*tim!=NULL) {
        starttime+=*(tim++);
    }*/
    QDateTime str =QDateTime::currentDateTime();
    QString endtime=str.toString("yyyy-MM-dd hh:mm:ss"); //还书时间
    QDateTime start=QDateTime::fromString(starttime,"yyyy-MM-dd hh:mm:ss");
    QDateTime end=QDateTime::fromString(endtime,"yyyy-MM-dd hh:mm:ss");
    uint stime=start.toTime_t();
    uint etime=end.toTime_t();
    int daysec=24*60*60;
    int day=(etime-stime)/(daysec)+((etime-stime)%(daysec)+(daysec-1))/(daysec);
    QString sql1="select * from T_USER where user_id="+usrid+";";
    QString sql2="select * from T_BOOK where book_id="+bookid+";";
    query.exec(sql1);
    if(!query.next()){
        QMessageBox::information(this,"警告","sql1执行失败");
        return;
    }
    QString usrname=query.value(1).toString();
    int number=query.value(3).toInt();
    query.exec(sql2);
    if(!query.next()){
        QMessageBox::information(this,"警告","sql2执行失败");
        return;
    }
    QString bkname=query.value(1).toString();
    QString status=query.value(5).toString();
    if(day>30){
       QString sql3="insert into T_RECORD(user_id,user_name,book_id,book_name,operation_type,operation_time) values("+usrid+",'"+usrname+"',"+bookid+",'"+bkname+"','还书','"+endtime+"');";
       query.exec(sql3);
       int money=day*0.2;
       QString rmoney=QString::number(money);
       QString sql4="insert into T_RECORD(user_id,user_name,book_id,book_name,operation_type,operation_time,fine_amount) values("+usrid+",'"+usrname+"',"+bookid+",'"+bkname+"','超期罚款','"+endtime+"',"+rmoney+");";
       query.exec(sql4);
       int num=number+1;
       QString nm=QString::number(num);
       QString sql5="update T_USER set available_number="+nm+" where user_id="+usrid+";";
       query.exec(sql5);
       QString sql6="update T_BOOK set book_status=0 where book_id="+bookid+";";
       query.exec(sql6);
       QMessageBox::warning(NULL, "温馨提示", "还书成功&超期处罚！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    else{
        QString sql7="insert into T_RECORD(user_id,user_name,book_id,book_name,operation_type,operation_time) values("+usrid+",'"+usrname+"',"+bookid+",'"+bkname+"','还书','"+endtime+"');";
        query.exec(sql7);
        int num=number+1;
        QString nm=QString::number(num);
        QString sql8="update T_USER set available_number="+nm+" where user_id="+usrid+";";
        query.exec(sql8);
        QString sql9="update T_BOOK set book_status=0 where book_id="+bookid+";";
        query.exec(sql9);
        QMessageBox::warning(NULL, "温馨提示", "还书成功！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    db.close();
}

void ReturnBookDlg::on_BtnLost_clicked()
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("myconn")){
        db=QSqlDatabase::database("myconn");
    }
    else{
        db=QSqlDatabase::addDatabase("QSQLITE","myconn");
    }
    db.setDatabaseName("./MyLibrary.db");
    if(!db.open()){
        QMessageBox::information(this,"警告","打开数据库失败");
        return;
    }
    QString usrid=ui->Edtuser->text();    //用户ID
    QString bookid=ui->Edtbook->text();       //书ID
    QString sql0="select * from T_RECORD where user_id="+usrid+" and book_id="+bookid+" and operation_type='借书' order by operation_time desc;";
    QSqlQuery query(db);
    query.exec(sql0);
    if(!query.next()){
        QMessageBox::information(this,"警告","sql0执行失败");
        return;
    }
    QString starttime=query.value(6).toString();
    QString usrname=query.value(2).toString();
    QDateTime str =QDateTime::currentDateTime();
    QString endtime=str.toString("yyyy-MM-dd hh:mm:ss"); //还书时间
    QDateTime start=QDateTime::fromString(starttime,"yyyy-MM-dd hh:mm:ss");
    QDateTime end=QDateTime::fromString(endtime,"yyyy-MM-dd hh:mm:ss");
    uint stime=start.toTime_t();
    uint etime=end.toTime_t();
    int daysec=24*60*60;
    int day=(etime-stime)/(daysec)+((etime-stime)%(daysec)+(daysec-1))/(daysec);
    QString sql1="select * from T_BOOK where book_id="+bookid+";";
    query.exec(sql1);
    if(!query.next()){
        QMessageBox::information(this,"警告","sql1执行失败");
        return;
    }
    QString bkname=query.value(1).toString();
    //QString status=query.value(5).toString();
    QString sql2="insert into T_RECORD(user_id,user_name,book_id,book_name,operation_type,operation_time) values("+usrid+",'"+usrname+"',"+bookid+",'"+bkname+"','丢书','"+endtime+"');";
    query.exec(sql2);
    QString sql3="delete from T_BOOK where book_id="+bookid+";";
    query.exec(sql3);
    db.close();
}

