#include "userdialog.h"
#include "ui_userdialog.h"

UserDialog::UserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDialog)
{
    ui->setupUi(this);
}

UserDialog::~UserDialog()
{
    delete ui;
}


void UserDialog::on_pushButton_AddUser_clicked()
{
/*
    //连接数据库
     QSqlDatabase db;
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
       else
       {
          QMessageBox::information(this,"成功","连接数据库成功");
          QString user_name=ui->lineEdit_UserName->text();//获取用户名
          QString user_status=ui->comboBox_Status->currentText();//获取用户身份
          QString free_number="5";
          if(user_status=="教师")
              free_number="10";
          QString sql="insert into T_USER(user_name,user_status,available_number)  values('"+user_name+"','"+user_status+"',"+free_number+");";
          QSqlQuery query(db);
          if(query.exec(sql))
             QMessageBox::information(this,"成功","插入用户信息成功");
          else
              QMessageBox::information(this,"失败","插入用户信息失败");
        }
       db.close();
       QSqlDatabase::removeDatabase("QSQLITE");
*/
}

void UserDialog::on_pushButton_ShowAll_clicked()
{
    model= new QSqlQueryModel(ui->tableView_User);
    ui->tableView_User->setModel(model);
    //连接数据库
    QSqlDatabase db;
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
    else
    {
       QMessageBox::information(this,"成功","连接数据库成功");
       QString sql="select *from  T_USER;";
       QSqlQuery query(db);
       query.exec(sql);
       if(!query.next())
       {
          QMessageBox::information(this,"错误","学生信息表格为空");
          return;
       }
       else
       {
           model->setQuery(sql,db);
           model->setHeaderData(0,Qt::Horizontal,tr("用户ID"));
           model->setHeaderData(1,Qt::Horizontal,tr("用户名"));
           model->setHeaderData(2,Qt::Horizontal,tr("身份"));
           model->setHeaderData(3,Qt::Horizontal,tr("可借阅数"));
           ui->tableView_User->setModel(model);
       }
       db.close();

     }
    QSqlDatabase::removeDatabase("QSQLITE");

}
