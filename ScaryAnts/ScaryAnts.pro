#-------------------------------------------------
#
# Project created by QtCreator 2015-12-04T10:13:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ScaryAnts
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    world.cpp \
    ant.cpp

HEADERS  += mainwindow.h \
    world.h \
    ant.h

FORMS    += mainwindow.ui
