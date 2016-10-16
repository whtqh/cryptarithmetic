#include "mainwindow.h"
#include <QApplication>
#include "cryptarithmetic/cryptarithmetic.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //call_times_func();

    return a.exec();
}
