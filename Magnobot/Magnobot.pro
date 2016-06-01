#-------------------------------------------------
#
# Project created by QtCreator 2016-04-18T16:35:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Magnobot
TEMPLATE = app


SOURCES += main.cpp\
        tablero.cpp \
    agente.cpp \
    nodo.cpp

HEADERS  += tablero.hpp \
    agente.hpp \
    nodo.hpp \
    ui_tablero.h

FORMS    += tablero.ui
