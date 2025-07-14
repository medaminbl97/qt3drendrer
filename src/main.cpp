#include <QApplication>
#include "mainwindow.h"
#include "ModelViewTabs.h"

int main(int argc, char *argv[])
{   
    QApplication a(argc, argv);

    Widget w;

    w.show();

    return a.exec();
}
