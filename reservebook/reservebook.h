#ifndef RESERVEBOOK_H
#define RESERVEBOOK_H

#include <QDialog>

namespace Ui {class ReserveBook;}

class ReserveBook : public QDialog {
    Q_OBJECT

public:
    explicit ReserveBook(QWidget *parent = 0);
    explicit ReserveBook(QModelIndex &index,QWidget *parent = 0);
    ~ReserveBook();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    int idbook = 0;
    int quantity = 0;
    int year = 0;
    QString title = "";
    QString author = "";
    QString publisher = "";
    QString isbn = "";
    Ui::ReserveBook *ui;
};

#endif // RESERVEBOOK_H
