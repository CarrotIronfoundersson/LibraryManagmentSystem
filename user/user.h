#ifndef USER_H
#define USER_H
#include <QTableView>
#include <QWidget>

namespace Ui {class User;}

class User : public QWidget {
    Q_OBJECT

public:

    explicit User(QString n,QWidget *parent = 0);
    ~User();

private slots:
    void on_pushButton_search_book_clicked();
    void on_pushButton_borrow_book_clicked();
    void on_pushButton_refresh_clicked();
    void on_pushButton_return_book_clicked();

private:
    QString accountName;
    Ui::User *ui;
};

#endif // READER_H
