#include "home.h"
#include "ui_home.h"
#include "ui_signin.h"
#include "signin/signin.h"
#include "database/database.h"
#include "ui_signup.h"
#include "signup/signup.h"
#include "database/database.h"
#include "searchbook/searchbook.h"

Home::Home(QWidget *parent) : QWidget(parent), ui(new Ui::Home) {
    ui->setupUi(this);
    this->on_pushButton_search_book_clicked();
}

Home::~Home() {delete ui;}

void Home::on_pushButton_search_book_clicked() {
    Database connection;
    if(!connection.openConnection()) {
        QMessageBox::critical(this, "Connection error! ", " Database failed to connect, contact system administrator.");
        return;
    }
    connection.closeConnection();

    SearchBook searchBook;
    ui->tableView->setModel(searchBook.search(ui->comboBox->currentText(), ui->lineEdit->text()));
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

