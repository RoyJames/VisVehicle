#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <iostream>
#include <QFile>
#include <QPalette>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setObjectName("mywindow");
    w.setStyleSheet("MainWindow#mywindow{ border-image : url(:/visual/mainwindowbg.png)}" );

    w.show();

    return a.exec();
}
