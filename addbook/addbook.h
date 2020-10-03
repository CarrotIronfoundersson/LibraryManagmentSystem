#ifndef ADDBOOK_H
#define ADDBOOK_H

#include <QDialog>

namespace Ui {class AddBook;}

class AddBook : public QDialog {
    Q_OBJECT

public:
    explicit AddBook(QWidget *parent = 0);
    explicit AddBook(QModelIndex &index,QWidget *parent = 0);
    ~AddBook();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    int idBook = 0;
    Ui::AddBook *ui;
    void on_button_modify_book_clicked();
};

#endif // ADDBOOK_H
