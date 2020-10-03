#-------------------------------------------------
#
# Project created by QtCreator 2020-07-21T12:28:34
#
#-------------------------------------------------

QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LMS
TEMPLATE = app
RC_FILE = LMS.rc

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    addbook/addbook.cpp \
    cancelreserve/cancelreserve.cpp \
    database/database.cpp \
    home/home.cpp \
    library_worker/library_worker.cpp \
    mainwindow/mainwindow.cpp \
    reservebook/reservebook.cpp \
    searchbook/searchbook.cpp \
    signin/signin.cpp \
    signup/signup.cpp \
    supplier/supplier.cpp \
    supplybook/supplybook.cpp \
    user/user.cpp \

HEADERS  += \
    addbook/addbook.h \
    cancelreserve/cancelreserve.h \
    database/database.h \
    home/home.h \
    library_worker/library_worker.h \
    mainwindow/mainwindow.h \
    reservebook/reservebook.h \
    searchbook/searchbook.h \
    signin/signin.h \
    signup/signup.h \
    supplier/supplier.h \
    supplybook/supplybook.h \
    user/user.h \

FORMS    += \
    addbook/addbook.ui \
    cancelreserve/cancelreserve.ui \
    home/home.ui \
    library_worker/library_worker.ui \
    mainwindow/mainwindow.ui \
    user/user.ui \
    reservebook/reservebook.ui \
    signin/signin.ui \
    signup/signup.ui \
    supplier/supplier.ui \
    supplybook/supplybook.ui \

RESOURCES +=  src.qrc

DISTFILES += \
    database/database.sqlite \
    database/rules.txt \
    images/add.png \
    images/acc.png \
    images/addbook.png \
    images/b.png \
    images/borrow.png \
    images/cancel.jpg \
    images/confirm.png \
    images/confirm2.png \
    images/deletebook-icon.png \
    images/home.ico \
    images/Home.png \
    images/iconwindow.ico \
    images/iconwindow.png \
    images/modify.png \
    images/receive.png \
    images/refresh.png \
    images/return.png \
    images/search-icon.png \
    images/signin.ico \
    images/signout.ico \
    images/signupicon.png \
    images/team.png \
