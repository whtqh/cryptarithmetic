#include "PuzzleButton.h"
PuzzleButton::PuzzleButton(QWidget *parent,int i,int j)
    :QPushButton(parent)
{
    num = -1;
    layout = ' ';
    this->setMinimumSize(50,50);
    this->setStyleSheet("QPushButton { background-color: #214b3f;font-size: 26pt;font-weight: bold;color: #ffffff;}");
    Matrix_i = i;
    Matrix_j = j;
}
PuzzleButton::~PuzzleButton(void)
{

}
void PuzzleButton::mousePressEvent(QMouseEvent *event)
{
    QPushButton::mousePressEvent(event);
    if(event->button() == Qt::LeftButton)
        emit Num_Increase(Matrix_i,Matrix_j);
}

void PuzzleButton::ButtonMenu()
{
    cout << layout<<endl;
}
