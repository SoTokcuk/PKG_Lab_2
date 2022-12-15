#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedHeight(900);
    w.setFixedWidth(1000);
    w.show();
    return a.exec();
}
