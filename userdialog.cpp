#include "userdialog.h"
#include "ui_userdialog.h"

UserDialog::UserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDialog)
{
    ui->setupUi(this);
    pUserUpdateDlg=NULL;
    mymodel=0;
}

UserDialog::~UserDialog()
{
    delete ui;
}

void UserDialog:: refreshTable()
{
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

       //success
    if(0==mymodel)
    {
        model= new QSqlQueryModel(ui->tableView_User);
        mymodel=1;
    }
    QString sql="select *from T_USER";
    model->setQuery(sql,db);
    model->setHeaderData(0,Qt::Horizontal,tr("用户ID"));
    model->setHeaderData(1,Qt::Horizontal,tr("用户名"));
    model->setHeaderData(2,Qt::Horizontal,tr("身份"));
    model->setHeaderData(3,Qt::Horizontal,tr("可借阅数"));
    ui->tableView_User->setModel(model);

}


void UserDialog::on_pushButton_AddUser_clicked()
{
    if(""==ui->lineEdit_UserName->text())
    {
         QMessageBox::information(this,"失败","用户名不能为空，请您先填写用户名。");
         return;
    }
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
          {
              QMessageBox::information(this,"成功","插入用户信息成功");
              refreshTable();

          }
          else
              QMessageBox::information(this,"失败","插入用户信息失败");
        }
       db.close();
       QSqlDatabase::removeDatabase("QSQLITE");

}

void UserDialog::on_pushButton_ShowAll_clicked()
{
    model= new QSqlQueryModel(ui->tableView_User);
    ui->tableView_User->setModel(model);
    mymodel=1;
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
          QMessageBox::information(this,"错误","数据库用户信息表格为空");
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

void UserDialog::on_pushButton_Delete_clicked()
{
    if(mymodel==0)
    {
        QMessageBox::information(this,"错误","请先显示加载所有用户信息，在表格中选择记录来完成删除操作。");
        return;
    }
    if(ui->tableView_User->model()->rowCount()==0)
    {
        QMessageBox::information(this,"错误","请先显示加载所有用户信息，在表格中选择记录来完成删除操作。");
        return;
    }
    QModelIndex index=ui->tableView_User->currentIndex();
    int curRow=index.row();
    if (curRow<0)
    {
        QMessageBox::information(this,"错误","请先显示加载所有用户信息，在表格中选择记录来完成删除操作。");
        return;
    }
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
    QString user_id=index.sibling(curRow,0).data().toString();
    QSqlQuery query(db);
    QString sql="delete from T_USER where user_id="+user_id+";";
    if(!query.exec(sql))
    {
        QMessageBox::information(this,"error","删除失败.");
        return;
    }

    //refresh
    refreshTable();
    db.close();
    QSqlDatabase::removeDatabase("QSQLITE");
    QMessageBox::information(this,"OK","删除成功.");
}

void UserDialog::on_pushButton_Update_clicked()
{
    if(mymodel==0)
    {
        QMessageBox::information(this,"错误","请先显示加载所有用户信息，在表格中选择记录来完成删除操作。");
        return;
    }
    if(ui->tableView_User->model()->rowCount()==0)
    {
        QMessageBox::information(this,"错误","请先显示加载所有用户信息，在表格中选择记录来完成删除操作。");
        return;
    }
    //
    QModelIndex index=ui->tableView_User->currentIndex();
    int curRow=index.row();
    if(curRow<0)
    {
        QMessageBox::information(this,"错误","请您先在表格当中单机选择您要更新的对象");
        return;
    }
    QString user_id=index.sibling(curRow,0).data().toString();
    QString user_name=index.sibling(curRow,1).data().toString();
    QString user_status=index.sibling(curRow,2).data().toString();
    //
    pUserUpdateDlg = new UserUpdateDialog(this);
    pUserUpdateDlg->setModal(false);
    connect(this,SIGNAL(sendMyRow(QString ,QString ,QString)),pUserUpdateDlg,SLOT(getMessage(QString ,QString ,QString)));
    emit sendMyRow(user_id,user_name ,user_status);
    if(pUserUpdateDlg->exec()==QDialog::Accepted)
    {
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
        QString sql="update  T_USER set user_name='"+pUserUpdateDlg->USER_NAME+"' where user_id="+user_id+";";
        QSqlQuery query(db);
        if(!query.exec(sql))
        {
            QMessageBox::information(this,"error","更新失败");
            return;
        }
        db.close();
        QMessageBox::information(this,"OK","更新成功.");
        refreshTable();
    }

}
