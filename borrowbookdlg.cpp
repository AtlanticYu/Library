#include "borrowbookdlg.h"
#include "ui_borrowbookdlg.h"
#include "sqlite3.h"
#include <QMessageBox>
#include <QDateTime>
BorrowBookDlg::BorrowBookDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BorrowBookDlg)
{
    ui->setupUi(this);
}

BorrowBookDlg::~BorrowBookDlg()
{
    delete ui;
}

void BorrowBookDlg::on_Btnsearch_clicked()
{
    //int row=ui->tableWidget->currentRow();
    ShowBook();
}

void BorrowBookDlg::on_BtnBorrow_clicked()
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
          QMessageBox::information(this,"db failed","++");
          return;
      }
      QString usrid=ui->Edtuserid->text();
      QString bkid=ui->Edtbkid->text();
      QString sql="select * from T_USER where user_id="+usrid+";";
      QSqlQuery query(db);
      bool a=query.exec(sql);
      if(!query.next()){
          QMessageBox::information(this,"警告","不存在的用户");
          return;
      }
      else{
      QString usrname=query.value("user_name").toString();
      int result=query.value("available_number").toInt();
      if(result==0){
          QMessageBox::warning(NULL, "警告", "您借书次数不足！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
      }
      else{
          db.open();
          QString sql0="select * from T_BOOK where book_id="+bkid+";";
          bool c=query.exec(sql0);
          if(!query.next()){
              QMessageBox::information(this,"警告","sql0执行失败");
              return;
          }
          QString bkname=query.value("book_name").toString();
          int status=query.value("book_status").toInt();
          if(status==1){
              QMessageBox::information(this,"警告","该书已借出");
          }
          else{
          QDateTime time =QDateTime::currentDateTime();
          QString str=time.toString("yyyy-MM-dd hh:mm:ss");
          db.close();
          int number=result-1;
          QString num;
          num=QString::number(number);
          QString sql1="update T_USER set available_number="+num+" where user_id="+usrid+";";
          QString sql2="update T_BOOK set book_status=1 where book_id="+bkid+";";
          QString sql3="insert into T_RECORD(user_id,user_name,book_id,book_name,operation_type,operation_time) values("+usrid+",'"+usrname+"',"+bkid+",'"+bkname+"','借书','"+str+"');";
          //bool m=query.exec(sql2);
          sqlite3 *pDb;
          sqlite3_stmt *Ustmt;
          sqlite3_open("./MyLibrary.db",&pDb);
          char *errmsg;
          if(sqlite3_exec(pDb,sql2.toStdString().c_str(),NULL,NULL,&errmsg)==SQLITE_OK){
              QMessageBox::warning(NULL, "温馨提示", "更新书籍状态成功！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
          }
          if(sqlite3_exec(pDb,sql1.toStdString().c_str(),NULL,NULL,&errmsg)==SQLITE_OK){
              QMessageBox::warning(NULL, "温馨提示", "更新用户借阅次数成功！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
          }
          if(sqlite3_exec(pDb,sql3.toStdString().c_str(),NULL,NULL,&errmsg)==SQLITE_OK){
              QMessageBox::warning(NULL, "温馨提示", "插入借阅记录成功！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
          }
          }
      }
      }
      ShowBook();
}

void BorrowBookDlg::ShowBook()
{
    for(int i=0;i<=ui->tableWidget->rowCount();i++){
        ui->tableWidget->removeRow(i);
    }
    sqlite3 *pDb;
    if(sqlite3_open("./MyLibrary.db",&pDb)==SQLITE_OK){
        QString id=ui->Edtbkid->text();
        QString sql="select book_id,book_name,press_name,book_status from T_BOOK where book_id="+id+";";
        sqlite3_stmt *pStmt;
        if(sqlite3_prepare(pDb,sql.toStdString().c_str(),sql.length(),&pStmt,nullptr)==SQLITE_OK){
            while(sqlite3_step(pStmt)==SQLITE_ROW){

            const unsigned char *bBkid=sqlite3_column_text(pStmt,0);
            const unsigned char *bBkname=sqlite3_column_text(pStmt,1);
            const unsigned char *bBPname=sqlite3_column_text(pStmt,2);
            const unsigned char *bBkstatus=sqlite3_column_text(pStmt,3);
            QTableWidgetItem *bBkidItem=new QTableWidgetItem((char *)bBkid);
            ui->tableWidget->insertRow(0);
            ui->tableWidget->setItem(0,0,bBkidItem);
            QTableWidgetItem *bBknameItem=new QTableWidgetItem((char *)bBkname);
            ui->tableWidget->setItem(0,1,bBknameItem);
            QTableWidgetItem *bBPnameItem=new QTableWidgetItem((char *)bBPname);
            ui->tableWidget->setItem(0,2,bBPnameItem);
            QTableWidgetItem *bBkstatusItem=new QTableWidgetItem((char *)bBkstatus);
            ui->tableWidget->setItem(0,3,bBkstatusItem);
     //       return;
            }
    //        QMessageBox::information(this,"警告","该书不存在");
        }
        sqlite3_close(pDb);
    }
}
