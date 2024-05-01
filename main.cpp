#include "mainwi.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWi w(0);
    w.show();
    return a.exec();
}
