#ifndef GAME
#define GAME


#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>


class Game: public QGraphicsView {

public:
    Game(QWidget * parent = 0);
    QGraphicsScene * scene;
};

#endif // GAME
