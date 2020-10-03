#include "signup.h"
#include "ui_signup.h"
#include "database/database.h"
#include <QMessageBox>
#include <QSql>
#include <QDateTime>

SignUp::SignUp(QWidget *parent) : QDialog(parent), ui(new Ui::SignUp) {
    ui->setupUi(this);
    this->setFixedSize(435,543);

    QFile file(QCoreApplication::applicationDirPath() + "/rules.txt");
    if(!file.exists()) QMessageBox::about(this, "Error open file", "Could not open rulex.txt");

    QString line;
    ui->plainTextEdit_rules->clear();
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        while (!stream.atEnd()){
            line = stream.readLine();
            ui->plainTextEdit_rules->setPlainText(ui->plainTextEdit_rules->toPlainText()+line+"\n");
        }
        ui->plainTextEdit_rules->setTextInteractionFlags(Qt::TextSelectableByKeyboard);
    }
    file.close();
}

SignUp::~SignUp() {delete ui;}

void SignUp::on_pushButton_cancel_clicked() {this->close();}

void SignUp::on_pushButton_ok_clicked() {
    Database connection;
    if(!connection.openConnection()){
        QMessageBox::critical(this,"Database Error!","Error Connecting to Database! Please try again or Check Database.");
        return;
    }
    QSqlQuery query;

    QString accountName =  ui->lineEdit_accountname->text();
    QString accountPassword = ui->lineEdit_password -> text();
    QString confirmPassword = ui->lineEdit_confirm_password -> text();
    QString email = ui->lineEdit_email->text() + '@' + ui->lineEdit_email2->text() + ui->comboBox_domen->currentText();
    QString fullName =  ui->lineEdit_fullname -> text();
    QString dayOfBirth = ui->spinBox_day->text() + '/' + ui->spinBox_month->text() +'/'+ ui->spinBox_year->text() ;
    if (accountName == "" || accountPassword  == "" || confirmPassword == "" || email == "" || fullName == "") {
        QMessageBox :: warning (this, "Error ", "You must fill out all required fields");
    } else if(query.exec("SELECT User_name FROM Accounts WHERE User_name ='" + accountName +"';") && query.next())
        QMessageBox :: warning (this, "Error "," Account name has been taken");
    else if (confirmPassword != accountPassword) {
        QMessageBox :: warning (this, "Error", "Password does not match!");
        ui->lineEdit_password ->setText ("");
        ui->lineEdit_confirm_password ->setText ("");
    } else if (!(ui->check_box_read->isChecked())) QMessageBox::warning(this,"Error "," You have not read the rule!");
    else {
        query.prepare("INSERT INTO Users VALUES(:Full_name, :User_name, :Email, :DOB);");
        query.bindValue(":Full_name", fullName);
        query.bindValue(":Email", email);
        query.bindValue(":DOB", dayOfBirth);
        query.bindValue(":User_name", accountName);
        query.exec();

        query.prepare("INSERT INTO Accounts VALUES(:ID_card, :User_name, :Password, :Role_ID, :Active);");
        query.bindValue(":User_name", accountName);
        query.bindValue(":Password", accountPassword);
        query.bindValue(":Role_ID", 1);
        query.bindValue(":Active", "false");
        query.exec();
        QMessageBox :: about (this, "Congratulations! ","You have successfully registered!\n"
                                                        "Ask library worker to activate your account!");
        connection.closeConnection();
        this->close();
    }
}
