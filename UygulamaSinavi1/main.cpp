#include "mainwindow.h"

#include <QApplication>


int oyuncu1=-99;
int oyuncu2=-99;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
