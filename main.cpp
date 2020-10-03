#include "mainwindow/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {

    QApplication application(argc, argv);
    MainWindow *mainWindow = new MainWindow();
    mainWindow->setWindowTitle("Library Managment System");
    mainWindow->show();
    return application.exec();
}
