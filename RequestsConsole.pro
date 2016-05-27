#-------------------------------------------------
#
# Project created by QtCreator 2016-05-25T17:22:08
#
#-------------------------------------------------

QT       += core gui\
            sql\

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RequestsConsole
TEMPLATE = app


SOURCES += main.cpp\
    connectdialog.cpp \
    mainwindow.cpp

HEADERS  += \
    connectdialog.h \
    mainwindow.h

FORMS += \
    form.ui
