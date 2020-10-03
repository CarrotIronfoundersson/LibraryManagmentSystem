#ifndef CANCELRESERVE_H
#define CANCELRESERVE_H


#include <QDialog>

namespace Ui {class CancelReserve;}

class CancelReserve : public QDialog {
    Q_OBJECT

public:
    explicit CancelReserve(QWidget *parent = 0);
    explicit CancelReserve(QModelIndex &index,QWidget *parent = 0);
    ~CancelReserve();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    int idbook = 0;
    int books_quantity = 0;
    int quantity = 0;
    int year = 0;
    QString title = "";
    QString author = "";
    QString publisher = "";
    QString isbn = "";
    QString reason = "";
    Ui::CancelReserve *ui;
};

#endif // CANCELRESERVE_H
