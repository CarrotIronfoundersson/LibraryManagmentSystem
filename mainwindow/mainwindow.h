#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "signin/signin.h"
namespace Ui {class MainWindow;}

class MainWindow : public QMainWindow {
public:
    Q_OBJECT

public:
    explicit MainWindow(int roleId, QString name, QWidget * par = 0);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionSignUp_triggered();
    void on_actionSignIn_triggered();
    void on_actionSignOut_triggered();
    void on_actionHome_triggered();
    void on_actionabout_triggered();

private:
    int roleId = 0;
    bool accActive = false;
    QString accountName = "";
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
