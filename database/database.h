#ifndef DATABASE_H
#define DATABASE_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include <QFileInfo>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>

class Database {
public:
    Database();
    QSqlDatabase db;
    QString path;
    bool openConnection();
    void closeConnection();
};

#endif // DATABASE_H
