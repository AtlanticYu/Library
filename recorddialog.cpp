#include "recorddialog.h"
#include "ui_recorddialog.h"

RecordDialog::RecordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecordDialog)
{
    ui->setupUi(this);
    mymodel=0;
}

RecordDialog::~RecordDialog()
{
    delete ui;
}

void RecordDialog::on_pushButton_UserId_clicked()
{
    //clear
    model= new QSqlQueryModel(ui->tableView_record);
    mymodel=1;
    ui->tableView_record->setModel(model);
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
          QString user_id=ui->lineEdit_UserId->text();
          QString sql="select *from  T_RECORD where user_id="+user_id+";";
          QSqlQuery query(db);
          query.exec(sql);
          if(!query.next())
          {
             QMessageBox::information(this,"错误","不存在该ID用户的操作记录");
             return;
          }
          else
          {
              model->setQuery(sql,db);
              model->removeColumn(0);//不显示记录ID列
              model->setHeaderData(0,Qt::Horizontal,tr("用户ID"));
              model->setHeaderData(1,Qt::Horizontal,tr("用户名"));
              model->setHeaderData(2,Qt::Horizontal,tr("书ID"));
              model->setHeaderData(3,Qt::Horizontal,tr("书名"));
              model->setHeaderData(4,Qt::Horizontal,tr("操作类型"));
              model->setHeaderData(5,Qt::Horizontal,tr("操作时间"));
              model->setHeaderData(6,Qt::Horizontal,tr("罚款金额"));
              ui->tableView_record->setModel(model);
          }
          db.close();
          QSqlDatabase::removeDatabase("QSQLITE");
        }


}

void RecordDialog::on_pushButton_BookId_clicked()
{
    //clear
    model= new QSqlQueryModel(ui->tableView_record);
    ui->tableView_record->setModel(model);
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
          QString book_id=ui->lineEdit_BookId->text();
          QString sql="select *from  T_RECORD where book_id="+book_id+";";
          QSqlQuery query(db);
          query.exec(sql);
          if(!query.next())
          {
             QMessageBox::information(this,"错误","不存在该ID书本的借阅记录");
             return;
          }
          else
          {
              model->setQuery(sql,db);
              model->removeColumn(0);//不显示记录ID列
              model->setHeaderData(0,Qt::Horizontal,tr("用户ID"));
              model->setHeaderData(1,Qt::Horizontal,tr("用户名"));
              model->setHeaderData(2,Qt::Horizontal,tr("书ID"));
              model->setHeaderData(3,Qt::Horizontal,tr("书名"));
              model->setHeaderData(4,Qt::Horizontal,tr("操作类型"));
              model->setHeaderData(5,Qt::Horizontal,tr("操作时间"));
              model->setHeaderData(6,Qt::Horizontal,tr("罚款金额"));
              ui->tableView_record->setModel(model);
          }
          db.close();
          QSqlDatabase::removeDatabase("QSQLITE");
        }

}

void RecordDialog::on_pushButton_ShowAll_clicked()
{
    //clear
    model= new QSqlQueryModel(ui->tableView_record);
    ui->tableView_record->setModel(model);
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
       QString sql="select *from  T_RECORD;";
       QSqlQuery query(db);
       query.exec(sql);
       if(!query.next())
       {
          QMessageBox::information(this,"错误","操作记录表为空");
          return;
       }
       else
       {
           model->setQuery(sql,db);
           model->removeColumn(0);//不显示记录ID列
           model->setHeaderData(0,Qt::Horizontal,tr("用户ID"));
           model->setHeaderData(1,Qt::Horizontal,tr("用户名"));
           model->setHeaderData(2,Qt::Horizontal,tr("书ID"));
           model->setHeaderData(3,Qt::Horizontal,tr("书名"));
           model->setHeaderData(4,Qt::Horizontal,tr("操作类型"));
           model->setHeaderData(5,Qt::Horizontal,tr("操作时间"));
           model->setHeaderData(6,Qt::Horizontal,tr("罚款金额"));
           ui->tableView_record->setModel(model);
       }
       db.close();
       QSqlDatabase::removeDatabase("QSQLITE");
     }

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
    int status=getStatus();
    switch (status)
    {
        case 0:QMessageBox::information(this,"000","000");break;
        case 1:QMessageBox::information(this,"111","111");break;
        case 2:QMessageBox::information(this,"222","222");break;
        case 3:QMessageBox::information(this,"333","333");break;
        case 4:QMessageBox::information(this,"444","444");break;
        case 5:QMessageBox::information(this,"555","555");break;
        case 6:QMessageBox::information(this,"666","666");break;
        case 7:QMessageBox::information(this,"7777","7777");break;
        default:QMessageBox::information(this,"....","default");break;
    }


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
