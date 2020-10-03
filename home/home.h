#ifndef HOME_H
#define HOME_H

#include <QWidget>

namespace Ui {class Home;}

class Home : public QWidget {
    Q_OBJECT

public:
    explicit Home(QWidget *parent = 0);
    ~Home();

private slots:
    void on_pushButton_search_book_clicked();


private:
    Ui::Home *ui;
};

#endif // HOME_H
