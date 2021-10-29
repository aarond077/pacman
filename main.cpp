#include <iostream>
#include <QApplication>
#include "simulation.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    simulation w;
    w.show();
    return a.exec();
}