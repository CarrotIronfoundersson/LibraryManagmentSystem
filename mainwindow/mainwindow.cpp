#include "database/database.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signup/signup.h"
#include "ui_supplier.h"
#include "ui_library_worker.h"
#include "ui_user.h"
#include "user/user.h"
#include "supplier/supplier.h"
#include "ui_home.h"
#include "home/home.h"
#include "library_worker/library_worker.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSql>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setFixedSize(715,650);
    ui->tabWidget->close();
    ui->toolBar->close();
    Home *home = new Home();
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(home);
    QWidget *p = new QWidget();
    p->setLayout(layout);
    setCentralWidget(p);
}

MainWindow::MainWindow(int roleId, QString name, QWidget *par) : QMainWindow(par), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->toolBar_2->close();
    accountName = name;
    if (roleId==1) {
        User *pUser = new User(accountName);
        ui->tabWidget->addTab(pUser, QString("User"));
    }
    if(roleId==2) {
        LibraryWorker *pLibraryWorker = new LibraryWorker();
        ui->tabWidget->addTab(pLibraryWorker, QString("Library worker"));
    }
    if(roleId==3) {
        Supplier *pSupplier = new Supplier(accountName);
        ui->tabWidget->addTab(pSupplier, QString("Supplier"));
    }
    if(roleId==4) {
        User *pUser = new User(accountName);
        ui->tabWidget->addTab(pUser, QString("User"));
        LibraryWorker *pLibraryWorker = new LibraryWorker();
        ui->tabWidget->addTab(pLibraryWorker, QString("Library worker"));
        Supplier *pSupplier = new Supplier(accountName);
        ui->tabWidget->addTab(pSupplier, QString("Supplier"));
    }
}

MainWindow::~MainWindow() {delete ui;}

void MainWindow::on_actionSignUp_triggered() {
    SignUp  signUp;
    signUp.exec();
}

void MainWindow::on_actionSignIn_triggered() {
    this->deleteLater();
    SignIn signIn;
    signIn.exec();
}

void MainWindow::on_actionSignOut_triggered() {this->deleteLater();}

void MainWindow::on_actionHome_triggered() {
    this->deleteLater();
    MainWindow * mainWindow = new MainWindow();
    mainWindow->setWindowTitle("Home page");
    mainWindow->show();
}

void MainWindow::on_actionabout_triggered() {
    QMessageBox::information(this, "Project team:", "<p>github.com/CarrotIronfoundersson</p>");
}
