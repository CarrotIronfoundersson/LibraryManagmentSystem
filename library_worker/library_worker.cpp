#include "library_worker.h"
#include "ui_library_worker.h"
#include "database/database.h"
#include "addbook/addbook.h"
#include "ui_addbook.h"
#include "reservebook/reservebook.h"
#include "ui_reservebook.h"
#include "cancelreserve/cancelreserve.h"
#include "ui_cancelreserve.h"
#include "searchbook/searchbook.h"

LibraryWorker::LibraryWorker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LibraryWorker) {
    ui->setupUi(this);
    this->on_pushButton_refresh_clicked();
}

LibraryWorker::~LibraryWorker() {delete ui;}

void LibraryWorker::on_pushButton_search_book_clicked() {
    SearchBook searchBook;
    ui->tableView_books->setModel(searchBook.search(ui->comboBox_2->currentText(), ui->lineEdit_search_book->text()));
    ui->tableView_books->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void LibraryWorker::on_pushButton_refresh_clicked() {
    Database connection;
    connection.openConnection();
    QSqlQuery query;
    QSqlQueryModel *returnBookRequestsModel = new QSqlQueryModel;
    QSqlQueryModel *membershipRequestsModel = new QSqlQueryModel;
    QSqlQueryModel *suppliedBooksModel = new QSqlQueryModel;
    QSqlQueryModel *reservedBooksModel = new QSqlQueryModel;

    query.exec("SELECT User, Book_ID, Title, Quantity, Borrow_date, Duration FROM Borrowed_books WHERE Status = 'false'");
    returnBookRequestsModel->setQuery(query);
    ui->tableView_requests_for_return_book->setModel(returnBookRequestsModel);
    ui->tableView_requests_for_return_book->setSelectionBehavior(QAbstractItemView::SelectRows);

    query.exec("SELECT ID_Card, User_name, Active FROM Accounts WHERE Role_ID = 1 AND Active = 'false' ");
    membershipRequestsModel->setQuery(query);
    ui->tableView_membership->setModel(membershipRequestsModel);
    ui->tableView_membership->setSelectionBehavior(QAbstractItemView::SelectRows);

    query.exec("SELECT * FROM Supplied_books");
    suppliedBooksModel->setQuery(query);
    ui->tableView_supplied_books->setModel(suppliedBooksModel);
    ui->tableView_supplied_books->setSelectionBehavior(QAbstractItemView::SelectRows);

    query.exec("SELECT * FROM Reserved_books");
    reservedBooksModel->setQuery(query);
    ui->tableView_reserved_books->setModel(reservedBooksModel);
    ui->tableView_reserved_books->setSelectionBehavior(QAbstractItemView::SelectRows);

    connection.closeConnection();
    this->on_pushButton_search_book_clicked();
}

void LibraryWorker::on_pushButton_add_book_clicked() {
    AddBook newBook;
    newBook.exec();
    this->on_pushButton_refresh_clicked();
}

void LibraryWorker::on_pushButton_reserve_book_clicked() {
    QModelIndex index = ui->tableView_books->currentIndex();

    if (!index.isValid()) QMessageBox::about(this, "Error", "Select the book for reservation first");
    else {
        ReserveBook reserveBook(index,0);
        reserveBook.exec();
        this->on_pushButton_refresh_clicked();
    }
}

void LibraryWorker::on_pushButton_cancel_reservation_clicked() {
    QModelIndex index = ui->tableView_reserved_books->currentIndex();

    if (!index.isValid()) QMessageBox::about(this, "Error", "Select the book for cancel reservation first");
    else {
        CancelReserve cancelReserve(index,0);
        cancelReserve.exec();
        this->on_pushButton_refresh_clicked();
    }
}

void LibraryWorker::on_pushButton_delete_book_clicked(){
    QModelIndex index = ui->tableView_books->currentIndex();

    if (!index.isValid()) QMessageBox::about(this, "Error ", " Please select a book to delete");
    else {
        int row = index.row();
        int id = index.sibling(row, 6).data().toInt();
        Database connection;
        connection.openConnection();
        QSqlQuery query;
        query.prepare("DELETE FROM Books WHERE Book_ID = :id");
        query.bindValue(":id", id);

        QMessageBox deleteBookMessageBox;
        QPushButton *ok = deleteBookMessageBox.addButton(tr("Delete") ,QMessageBox::ActionRole);
        deleteBookMessageBox.addButton(tr("Cancel"),QMessageBox::NoRole);
        deleteBookMessageBox.setWindowTitle("Warning!");
        deleteBookMessageBox.setText("Book will be deleted from the system\nAre you sure you want to DELETE?");
        deleteBookMessageBox.exec();
        if(deleteBookMessageBox.clickedButton() == ok) {
            query.exec();
        }
        connection.closeConnection();
        this->on_pushButton_refresh_clicked();
    }
}

void LibraryWorker::on_pushButton_modify_book_clicked() {
    QModelIndex index = ui->tableView_books->currentIndex();

    if (!index.isValid()) QMessageBox::about(this,"Error", "Select the book to be edited first");
    else {
        AddBook modifyBook(index, 0);
        modifyBook.exec();
        this->on_pushButton_refresh_clicked();
    }
}

void LibraryWorker::on_pushButton_confirm_book_return_clicked() {
    QModelIndex index = ui->tableView_requests_for_return_book->currentIndex();

    if (!index.isValid()) QMessageBox::about(this,"Error "," You have not selected the object");
    else {
        QString user = index.sibling(index.row(), 0).data().toString();
        QString title = index.sibling(index.row(), 1).data().toString();
        QString now =  QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");

        Database connection;
        connection.openConnection();
        QSqlQuery query;

        query.prepare("SELECT Quantity FROM Books WHERE Book_ID = :id");
        query.bindValue(":id", index.sibling(index.row(), 1).data().toInt());
        query.exec();
        int quantity = 1;
        if (query.next()) quantity = query.value(0).toInt() + 1;

        QMessageBox::StandardButton confirm = QMessageBox::question(this,"","Confirm the User returns the book?",QMessageBox::Yes|QMessageBox::No);
        if (confirm == QMessageBox::Yes) {
            query.prepare("DELETE FROM Borrowed_books WHERE Book_ID = :id AND User = :user");
            query.bindValue(":id",index.sibling(index.row(), 1).data().toInt());
            query.bindValue(":user",user);
            query.exec();
            query.prepare("UPDATE Books SET Quantity = :quantity WHERE Book_ID = :id");
            query.bindValue(":id",index.sibling(index.row(), 1).data().toInt());
            query.bindValue(":quantity", quantity);
            query.exec();
        }
        connection.closeConnection();
        this->on_pushButton_refresh_clicked();
    }
}

void LibraryWorker::on_pushButton_cancel_book_return_clicked() {
    QModelIndex index = ui->tableView_requests_for_return_book->currentIndex();
    if (!index.isValid()) QMessageBox::about(this, "Error ", " Please select the object to cancel request");
    else {
        int id = index.sibling(index.row(), 1).data().toInt();
        QString user = index.sibling(index.row(), 0).data().toString();

        Database connection;
        connection.openConnection();
        QSqlQuery query;
        query.prepare("UPDATE Borrowed_books SET Status = 'true' WHERE Book_ID = :id AND User = :user");
        query.bindValue(":id", id);
        query.bindValue(":user", user);

        QMessageBox::StandardButton confirm = QMessageBox::question(this, "Confirm ", " Are you sure you want to cancel the request ?", QMessageBox::Yes | QMessageBox::No);
        if (confirm == QMessageBox::Yes) query.exec();

        connection.closeConnection();
        this->on_pushButton_refresh_clicked();
    }
}

void LibraryWorker::on_pushButton_confirm_membership_clicked() {
    QModelIndex index = ui->tableView_membership->currentIndex();
    if (!index.isValid()) QMessageBox::warning(this,"","No object selected.");
    else {
        Database connection;
        connection.openConnection();
        QSqlQuery query;
        query.prepare("UPDATE Accounts SET Active = 'true' WHERE User_name = :user");
        query.bindValue(":user", index.sibling(index.row(), 1).data().toString());

        QMessageBox::StandardButton confirm = QMessageBox::question(this, "", "Confirm the User membership?", QMessageBox::Yes | QMessageBox::No);
        if(confirm == QMessageBox::Yes) query.exec();

        connection.closeConnection();
        this->on_pushButton_refresh_clicked();
    }
}

void LibraryWorker::on_pushButton_receive_book_clicked() {
    QModelIndex index = ui->tableView_supplied_books->currentIndex();
    if (!index.isValid()) QMessageBox::warning(this,"","No object selected.");
    else {
        Database connection;
        connection.openConnection();
        QSqlQuery query;

        query.exec("SELECT * FROM Books;");
        int bookID = 1;
        if (query.last()) bookID = query.value(0).toInt() + 1;

        int supplyID = index.sibling(index.row(), 0).data().toInt();
        QString title = index.sibling(index.row(), 1).data().toString();
        QString author = index.sibling(index.row(), 2).data().toString();
        QString isbn = index.sibling(index.row(), 3).data().toString();
        QString publisher = index.sibling(index.row(), 4).data().toString();
        int year = index.sibling(index.row(), 5).data().toInt();
        int quantity = index.sibling(index.row(), 6).data().toInt();

        if ( query.exec("SELECT Quantity, ISBN, Title, Author, Publisher, Year FROM Books WHERE ISBN = '" + isbn + "';")
             && query.first()) {
            books_quantity = query.value(0).toInt();
            book_isbn = query.value(1).toString();
            book_title = query.value(2).toString();
            book_author = query.value(3).toString();
            book_publisher = query.value(4).toString();
            books_year = query.value(5).toInt();
        }

        QMessageBox::StandardButton confirm = QMessageBox::question(this, "Verify ", "Are you sure to receive this book? ", QMessageBox::Yes | QMessageBox::No);
        if (confirm == QMessageBox::Yes) {
            if (book_isbn == isbn && books_year == year && book_title == title && book_author == author && book_publisher == publisher) {
                query.prepare("UPDATE Books SET Quantity = :quantity WHERE ISBN = :isbn AND Title = :title");
                query.bindValue(":quantity", quantity + books_quantity);
                query.bindValue(":isbn", index.sibling(index.row(), 3).data().toString());
                query.bindValue(":title", index.sibling(index.row(), 1).data().toString());
            } else {
                query.prepare("INSERT INTO Books (Book_ID, Title, Author, ISBN, Publisher, Year, Quantity) "
                              "VALUES(:id, :title, :author, :isbn, :publisher, :year, :quantity);");
                query.bindValue(":id", bookID);
                query.bindValue(":title", title);
                query.bindValue(":author", author);
                query.bindValue(":isbn", isbn);
                query.bindValue(":publisher", publisher);
                query.bindValue(":year", year);
                query.bindValue(":quantity", quantity);
            }
            query.exec();
            query.prepare("DELETE FROM Supplied_books WHERE Book_ID = :id");
            query.bindValue(":id", supplyID);
            query.exec();
        }
        connection.closeConnection();
        this->on_pushButton_refresh_clicked();
    }
}
