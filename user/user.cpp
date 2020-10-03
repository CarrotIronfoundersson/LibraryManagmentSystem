#include "user.h"
#include "ui_user.h"
#include "signup/signup.h"
#include "database/database.h"
#include "signin/signin.h"
#include "searchbook/searchbook.h"

User::User(QString pAccountName,QWidget *parent) : QWidget(parent), ui(new Ui::User) {
    ui->setupUi(this);
    accountName = pAccountName;
    this->on_pushButton_refresh_clicked();
}

User::~User() {delete ui;}

void User::on_pushButton_search_book_clicked() {
    SearchBook searchBook;
    ui->tableView_books->setModel(searchBook.search(ui->comboBox->currentText(), ui->lineEdit_search_book->text()));
    ui->tableView_books->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void User::on_pushButton_refresh_clicked() {
    this->on_pushButton_search_book_clicked();

    Database connection ;
    connection.openConnection();
    QSqlQuery query;
    QSqlQueryModel *databaseModel = new QSqlQueryModel;
    query.prepare("select User, Book_ID, Title, Quantity, Borrow_date, Duration from Borrowed_books where User = :User and Status = 'true'  ");
    query.bindValue(":User", accountName);
    query.exec();

    databaseModel->setQuery(query);
    ui->tableView_borrowed_books->setModel(databaseModel);
    connection.closeConnection();
}

void User::on_pushButton_borrow_book_clicked() {
    QModelIndex index = ui->tableView_books->currentIndex();
    if (!index.isValid()) {
        QMessageBox::about(this,"Error ", " Please select a book first !");
    } else {
        QString now =  QDateTime::currentDateTime().toString("yyyy/MM/dd");
        QString title = index.sibling(index.row(), 0).data().toString();
        QString status = "true";
        int id = index.sibling(index.row(), 6).data().toInt();
        int quantity = index.sibling(index.row(), 4).data().toInt();

        Database connection;
        connection.openConnection();
        QSqlQuery query;

        query.prepare("Select Book_ID FROM Borrowed_books WHERE User = :user AND Book_ID = :id");
        query.bindValue(":user", accountName);
        query.bindValue(":id", id);

        if (query.exec() && query.next() && id == query.value(0).toInt()) {
            QMessageBox::about(this,"Unsuccessfull !","You can borrow only one copy of the book");
            connection.closeConnection();
            return;
        } else if (quantity == 1) {
            QMessageBox::about(this,"Last copy of book","Book avaible to read in the library only");
            connection.closeConnection();
            return;
        } else if (quantity < 1) {
            QMessageBox::about(this,"Out of stock","There is no available copy to borrow\nAsk library worker for help");
            connection.closeConnection();
            return;
        }

        QMessageBox::StandardButton confirm = QMessageBox::question(this,"","Do you want to borrow the book?",QMessageBox::Yes|QMessageBox::No);
        if (confirm == QMessageBox::Yes) {
            query.prepare("INSERT INTO Borrowed_books (Status,User,Book_ID,Title,Quantity,Borrow_date,Duration) "
                          "VALUES(:status,:user,:id,:title,:quantity,:date,:duration);");
            query.bindValue(":status", status);
            query.bindValue(":title", title);
            query.bindValue(":user", accountName);
            query.bindValue(":id", id);
            query.bindValue(":quantity", 1);
            query.bindValue(":date", now);
            query.bindValue(":duration", 30);
            query.exec();

            query.prepare("update Books set Quantity = :quantity where Book_ID = :id");
            query.bindValue(":id", id);
            query.bindValue(":quantity", --quantity);
            query.exec();
        }
        connection.closeConnection();
    }
    this->on_pushButton_refresh_clicked();
}

void User::on_pushButton_return_book_clicked() {
    QModelIndex index = ui->tableView_borrowed_books->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this,"", "No object selected.");
    } else {
        QString user = index.sibling(index.row(), 0).data().toString();
        QString title = index.sibling(index.row(), 1).data().toString();
        QString now = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");

        Database connection;
        connection.openConnection();
        QSqlQuery query;
        QMessageBox::StandardButton confirm = QMessageBox::question(this,"","You want to return the book?",QMessageBox::Yes|QMessageBox::No);
        if (confirm == QMessageBox::Yes) {
            query.prepare("update  Borrowed_books set Status = 'false' where Book_ID = :id AND User = :user");
            query.bindValue(":id",index.sibling(index.row(), 1).data().toInt());
            query.bindValue(":user", accountName);
            query.exec();
        }
        connection.closeConnection();
    }
    this->on_pushButton_refresh_clicked();
}
