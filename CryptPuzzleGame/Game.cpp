#include "Game.h"
#include <QGraphicsScene>
//#include <QGraphicsRectItem>
#include <QGraphicsView>




Game::Game(QWidget *parent)
{

    // scene
    scene = new QGraphicsScene();
    scene->setSceneRect(-100,-80,300,300);
    scene->addLine(0,0,150,200);

    // set backgroung image
    //setBackgroundBrush(QBrush(QImage(":/bg-images/bg-image.png")));


    // view *Game inherits View*
    this->setScene(scene);
    //this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //this->setFixedSize(950,725);
    this->show();
}
