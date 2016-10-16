#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QFont>
#include <QtWidgets/QApplication>
#include "PuzzleButton.h"
#include "cryptarithmetic/formula.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    formula* plus_formula;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene * scene;
    QWidget* formula;
    void FormulaShow();
};

#endif // MAINWINDOW_H
