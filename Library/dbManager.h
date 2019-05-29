#ifndef DBMANAGER_H
#define DBMANAGER_H
#include<QSqlQueryModel>
#include<QSqlQuery>
#include <QMessageBox>

class dbManager
{
private:
    QString connName;
    QString dbPath;
    QString dbType;
    QSqlDatabase db;

public:
    dbManager();
    bool setDBMessage(QString _dbType,QString _dbPath,QString _connName);
    QSqlDatabase getDB();

};

#endif // DBMANAGER_H
