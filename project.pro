#-------------------------------------------------
#
# Project created by QtCreator 2018-06-12T15:50:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    vertex.cpp \
    graph.cpp \
    bellmanmark.cpp \
    floydmark.cpp \
    displayframe.cpp \
    launchdialog.cpp \
    shortestpathwindow.cpp \
    common.cpp \
    setdistancedialog.cpp \
    vertexparam.cpp

HEADERS += \
    vertex.h \
    graph.h \
    common.h \
    bellmanmark.h \
    floydmark.h \
    displayframe.h \
    launchdialog.h \
    shortestpathwindow.h \
    setdistancedialog.h \
    vertexparam.h

FORMS += \
    launchdialog.ui \
    shortestpathwindow.ui \
    setdistancedialog.ui

