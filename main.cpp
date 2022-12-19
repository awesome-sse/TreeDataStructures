#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(w.width() * 1.2, w.height() * 1.2);

    w.show();
    return a.exec();
}
