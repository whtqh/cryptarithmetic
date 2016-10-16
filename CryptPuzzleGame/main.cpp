#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGridLayout>
#include "Game.h"
#include "cryptarithmetic/cryptarithmetic.h"



Game * game;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow game;

    game.setFixedSize(1080,720);
    game.show();

    return a.exec();
}
