#-------------------------------------------------
#
# Project created by QtCreator 2016-08-22T15:17:11
#
#-------------------------------------------------

QT       += core gui
QT       += webkitwidgets
QT       += sql
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VisVehicle
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    buttons.cpp \
    loaderbuttons.cpp \
    glwidget.cpp \
    testcategory.cpp \
    testsubcategory.cpp

HEADERS  += mainwindow.h \
    buttons.h \
    loaderbuttons.h \
    glwidget.h \
    testcategory.h \
    testsubcategory.h \
    definitions.h

INCLUDEPATH += $$quote(D:\Program Files\Matlab32\extern\include)

LIBS += -L$$quote(D:\Program Files\Matlab32\extern\lib\win32\microsoft) -llibeng -llibmat -llibmx -llibmex


FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
