#pragma once
#ifndef PUZZLEBUTTON_H
#define PUZZLEBUTTON_H
#include <QPushButton>
#include <QPainter>
class PuzzleButton:public QPushButton
{
public:
    int num;
    char layout;
    explicit PuzzleButton(QWidget *parent);
    virtual ~PuzzleButton(void);
};

#endif // PUZZLEBUTTON_H
