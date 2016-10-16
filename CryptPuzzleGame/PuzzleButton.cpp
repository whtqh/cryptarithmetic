#include "PuzzleButton.h"
PuzzleButton::PuzzleButton(QWidget *parent)
    :QPushButton(parent)
{
    num = -1;
    layout = ' ';
    this->setMinimumSize(50,50);
    this->setStyleSheet("QPushButton { background-color: #214b3f;font-size: 26pt;font-weight: bold;color: #ffffff;}");

}
PuzzleButton::~PuzzleButton(void)
{

}
