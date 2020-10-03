#include "database.h"

Database::Database() {
    if (!db.open()){
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(QCoreApplication::applicationDirPath()+"/database.sqlite");
    }
}

bool Database::openConnection(){
    db.open();
    db.exec("PRAGMA foreign_keys = ON");
    return db.open();
}

void Database::closeConnection(){
    db.close();
}
