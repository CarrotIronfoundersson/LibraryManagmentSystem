#ifndef LIBRARY_WORKER_H
#define LIBRARY_WORKER_H

#include <QWidget>
#include <QString>
#include <QTableView>

namespace Ui {class LibraryWorker;}

class LibraryWorker : public QWidget {
    Q_OBJECT

public:
    explicit LibraryWorker(QWidget *parent = 0);
    ~LibraryWorker();

private slots:
    void on_pushButton_confirm_book_return_clicked();
    void on_pushButton_cancel_book_return_clicked();
    void on_pushButton_confirm_membership_clicked();
    void on_pushButton_receive_book_clicked();
    void on_pushButton_cancel_reservation_clicked();
    void on_pushButton_refresh_clicked();
    void on_pushButton_search_book_clicked();
    void on_pushButton_add_book_clicked();
    void on_pushButton_modify_book_clicked();
    void on_pushButton_delete_book_clicked();
    void on_pushButton_reserve_book_clicked();

private:
    int books_quantity;
    int books_year;
    QString book_isbn;
    QString book_title;
    QString book_author;
    QString book_publisher;
    Ui::LibraryWorker *ui;


};

#endif // LIBRARY_WORKER_H
