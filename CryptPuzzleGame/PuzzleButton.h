#pragma once
#ifndef PUZZLEBUTTON_H
#define PUZZLEBUTTON_H
#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
#include <iostream>
using namespace std;
class PuzzleButton:public QPushButton
{
Q_OBJECT
public:
    int num;
    char layout;
    int Matrix_i;
    int Matrix_j;
    QMenu *menu;    //One Button one Menu~

    explicit PuzzleButton(QWidget *parent,int i,int j);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual ~PuzzleButton(void);
public slots:
    void ButtonMenu();
signals:
    void Num_Increase(int, int);
};

#endif // PUZZLEBUTTON_H
