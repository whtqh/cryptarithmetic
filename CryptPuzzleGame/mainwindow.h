#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QFont>
#include <QPen>
#include <QMenu>
#include <QGraphicsLineItem>
#include <QtWidgets/QApplication>
#include <QString>
#include "cryptarithmetic/formula.h"
#include "cryptarithmetic/cryptarithmetic.h"
namespace Ui {
class MainWindow;

}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int file_num;
    string file_path;
    QGraphicsLineItem *line;
    QMenu *menu;
    formula* plus_formula;
    PuzzleButton*** button_matrix;



    void FormulaShow();
    void FormulaPlusRead();     //Show Problem
    void FormulaMenuInitial();  //To solve problem
    void FormulaAnswerShow();   //To show the answers
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Button0_clicked();

    void on_Button3_clicked();

    void on_Button4_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene * scene;
    QWidget* formula_widget;

};

#endif // MAINWINDOW_H
