#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::addLibraryPath("G://Qt_Project//Base//emoji_game//plugins");
    MainWindow w;
    w.show();

    return a.exec();
}
