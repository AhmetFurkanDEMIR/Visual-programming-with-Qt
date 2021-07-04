#include "mainwindow.h"
#include <QApplication>

// monitorun boyutu
int heightH;
int widthW;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showFullScreen();
    return a.exec();
}
