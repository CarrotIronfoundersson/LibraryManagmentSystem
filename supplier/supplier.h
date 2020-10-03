#ifndef SUPPLIER_H
#define SUPPLIER_H
#include <QTableView>
#include <QWidget>

namespace Ui {class Supplier;}

class Supplier : public QWidget {
    Q_OBJECT

public:
    explicit Supplier(QString n, QWidget *parent = 0);
    ~Supplier();

private slots:
    void on_pushButton_search_book_clicked();
    void on_pushButton_refresh_clicked();
    void on_pushButton_supply_book_clicked();
    void on_pushButton_remove_supply_clicked();
    void on_pushButton_modify_supply_clicked();

private:
    QString accountName;
    Ui::Supplier *ui;
};

#endif // SUPPLIER_H
