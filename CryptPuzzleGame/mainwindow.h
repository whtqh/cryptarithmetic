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
#include <QIntValidator>
#include <QString>
#include "cryptarithmetic/formula.h"
#include "cryptarithmetic/cryptarithmetic.h"
#include "configuredialog.h"
#include "check_right_dialog.h"
#include "check_wrong_dialog.h"
namespace Ui {
class MainWindow;

}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int file_num;
    int* formula_kind;
    string file_path;
    QGraphicsLineItem *line;
    //QGraphicsEllipseItem *Ellipse;

    ConfigureDialog* QuestionBase;
    Check_Right_Dialog* Ans_Right;
    Check_Wrong_Dialog* Ans_Wrong;

    formula* plus_formula;
    minus_formula* mins_formula;
    times_formula* tims_formula;
    divide_formula* divd_formula;

    PuzzleButton*** button_matrix;


    //Add Func--------------------------------------------------
    void FormulaShow();         //To show the problem
    void FormulaPlusRead();     //Show Problem
    void FormulaMenuInitial();  //To Check problem
    void FormulaAnswerShow();   //To show the answers

    //Minus Func--------------------------------------------------
    void Minus_FormulaShow();         //To show the problem
    void Minus_FormulaPlusRead();     //Show Problem
    void Minus_FormulaMenuInitial();  //To Check problem
    void Minus_FormulaAnswerShow();   //To show the answers

    //tims Func--------------------------------------------------
    void Times_FormulaShow();         //To show the problem
    void Times_FormulaPlusRead();     //Show Problem
    void Times_FormulaMenuInitial();  //To Check problem
    void Times_FormulaAnswerShow();   //To show the answers

    //divd Func--------------------------------------------------
    void Divid_FormulaShow();         //To show the problem
    void Divid_FormulaPlusRead();     //Show Problem
    void Divid_FormulaMenuInitial();  //To Check problem
    void Divid_FormulaAnswerShow();   //To show the answers


    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_Button0_clicked();

    void on_Button3_clicked();

    void on_Button4_clicked();
    void TestMenu();
    void Increase_Num(int i, int j);
private:
    Ui::MainWindow *ui;
    QGraphicsScene * scene;
    QWidget* formula_widget;

};

#endif // MAINWINDOW_H
