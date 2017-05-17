#-------------------------------------------------
#
# Project created by QtCreator 2014-12-01T15:14:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Paint
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    renderarea.cpp

HEADERS  += mainwindow.h \
    renderarea.h

FORMS    += mainwindow.ui

RESOURCES += \
    Resources.qrc
