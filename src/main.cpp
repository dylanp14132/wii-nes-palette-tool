#include <QApplication>
#include <QStyleFactory>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("windowsvista"));
    MainWindow w;
    w.show();
    return QApplication::exec();
}
