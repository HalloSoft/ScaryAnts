#-------------------------------------------------
#
# Project created by QtCreator 2015-12-04T10:13:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ScaryAnts
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    world.cpp \
    ant.cpp \
    commonant.cpp \
    game.cpp \
    socialant.cpp

HEADERS  += mainwindow.h \
    world.h \
    ant.h \
    commonant.h \
    game.h \
    socialant.h

FORMS    += mainwindow.ui
