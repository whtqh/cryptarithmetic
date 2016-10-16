#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGridLayout>
#include "cryptarithmetic/cryptarithmetic.h"




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow game;

    game.setFixedSize(1080,720);
    game.show();
    game.FormulaPlusRead();

    //game.FormulaShow();
    return a.exec();
}
