#include "searchbook.h"


SearchBook::SearchBook() {};

QSqlQueryModel* SearchBook::search(QString searchType, QString searchWord) {
    Database connection;
    connection.openConnection();
    QSqlQueryModel* databaseModel = new QSqlQueryModel;
    QSqlQuery query;

    if (searchType == "ISBN")
        query.exec("SELECT Title, Author, Publisher, Year, Quantity, ISBN, Book_ID FROM Books WHERE ISBN LIKE '%'||'" + searchWord + "'||'%';");
    else if (searchType == "Title")
        query.exec("SELECT Title, Author, Publisher, Year, Quantity, ISBN, Book_ID FROM Books WHERE Title LIKE '%'||'" + searchWord + "'||'%';");
    else if (searchType == "Author")
        query.exec("SELECT Title, Author, Publisher, Year, Quantity, ISBN, Book_ID FROM Books WHERE Author LIKE '%'||'" + searchWord + "'||'%';");
    else if (searchType == "Year")
        query.exec("SELECT Title, Author, Publisher, Year, Quantity, ISBN, Book_ID FROM Books WHERE Year = '" + searchWord + "';");
    else if (searchType == "Publisher")
        query.exec("SELECT Title, Author, Publisher, Year, Quantity, ISBN, Book_ID FROM Books WHERE Publisher LIKE '%'||'" + searchWord + "'||'%';");
    else if (searchType == "All books")
        query.exec("SELECT Title, Author, Publisher, Year, Quantity, ISBN, Book_ID FROM Books;");

    databaseModel->setQuery(query);
    connection.closeConnection();
    return databaseModel;
}
