#include "signin.h"
#include "ui_signin.h"
#include "home/home.h"
#include "database/database.h"
#include "mainwindow/mainwindow.h"
#include "ui_mainwindow.h"

SignIn::SignIn(QWidget *parent) : QDialog(parent), ui(new Ui::SignIn) {
    ui->setupUi(this);
    this->setFixedSize(400,150);
}

SignIn::~SignIn() {delete ui;}

void SignIn::on_pushButton_login_clicked() {
    Database connection;
    if (!connection.openConnection()) {
        QMessageBox::about(this, "Error", "No connection to the database ");
        return;
    }

    QString accountName = ui->lineEdit_username->text();
    QString accountPassword = ui->lineEdit_password->text();
    QSqlQuery query;

    if(query.exec("select * from Accounts where User_name =\'" + accountName + "\' and Password =\'"+ accountPassword +"\'")
            && query.next()) {
        int roleId = query.value(3).toInt();
        bool isActive = query.value(4).toBool();
        if (!isActive) {
            QMessageBox::about(this,"Failed","Account <b>" + accountName + "</b> is locked :( Contact library worker for activation." );
            this->show();
        } else {
            QMessageBox::about(this, "Success ", "You logged in as <b>" + accountName +"</b>");
            this->close();
            MainWindow *n = new MainWindow(roleId, accountName, 0);
            n->setWindowTitle(accountName);
            n->show();
        }
    } else {
        QMessageBox::warning(this,"Login failed "," The account or password is incorrect");
        this->show();
    }
    connection.closeConnection();
}

void SignIn::on_pushButton_close_clicked() {
    MainWindow *mainWindow = new MainWindow();
    this->close();
    mainWindow->show();
}
