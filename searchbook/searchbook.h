#ifndef SEARCHBOOK_H
#define SEARCHBOOK_H

#include "database/database.h"
#include <QMessageBox>
//#include <QWidget>



class SearchBook {
public:
    SearchBook();
    QSqlQueryModel* search(QString searchType, QString searchWord);
};

#endif // SEARCHBOOK_H
