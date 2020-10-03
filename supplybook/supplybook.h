#ifndef SUPPLYBOOK_H
#define SUPPLYBOOK_H

#include <QDialog>

namespace Ui {class SupplyBook;}

class SupplyBook : public QDialog {
    Q_OBJECT

public:
    explicit SupplyBook(QWidget *parent = 0);
    explicit SupplyBook(QModelIndex &index,QWidget *parent = 0);
    ~SupplyBook();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    int idbook = 0;
    Ui::SupplyBook *ui;
    void on_button_modify_supply_clicked();
};

#endif // SUPPLYBOOK_H
