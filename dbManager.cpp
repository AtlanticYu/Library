#include "dbManager.h"

dbManager::dbManager()
{

}

bool dbManager::setDBMessage(QString _dbType,QString _dbPath,QString _connName)
{
   connName=_connName;
   dbPath=_dbPath;
   dbType=_dbType;
   return true;

}
QSqlDatabase dbManager::getDB()
{
     if (QSqlDatabase::contains(connName))
     {
        db = QSqlDatabase::database(connName);
     }
     else
     {
        db = QSqlDatabase::addDatabase(dbType, connName);//加载数据库驱动，并命名连接名称为connName
     }
     db.setDatabaseName(dbPath);
     return db;
}

