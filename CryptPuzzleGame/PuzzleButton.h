#ifndef PUZZLEBUTTON_H
#define PUZZLEBUTTON_H
#include <QPushButton>
#include "mainwindow.h"
#include <QPainter>
class PuzzleButton:public QPushButton
{
public:
    PuzzleButton(QWidget *parent);
    virtual ~PuzzleButton(void);

};

#endif // PUZZLEBUTTON_H
