#-------------------------------------------------
#
# Project created by QtCreator 2015-06-23T02:31:18
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MiLightBulbController
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ledclient.cpp \
    ledbridge.cpp

HEADERS  += mainwindow.h \
    ledcolor.h \
    ledcommands.h \
    ledclient.h \
    ledbridge.h

FORMS    += mainwindow.ui
