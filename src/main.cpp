#include <QApplication>
#include <QFile>
#include "mainwindow.h"
#include "ModelViewTabs.h"


void loadStyleSheet(QApplication &app, const QString &qssResourcePath);



int main(int argc, char *argv[])
{   
    QApplication a(argc, argv);
    loadStyleSheet(a, ":/Medize.qss");
    Widget w;

    w.show();

    return a.exec();
}



void loadStyleSheet(QApplication &app, const QString &qssResourcePath)
{
    QFile file(qssResourcePath);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = file.readAll();
        app.setStyleSheet(styleSheet);
        file.close();
    } else {
        qWarning("Unable to load QSS from resource: %s", qPrintable(qssResourcePath));
    }
}
