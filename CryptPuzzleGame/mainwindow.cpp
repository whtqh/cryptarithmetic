#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    file_num = 0;
    file_path = "..\\CryptPuzzleGame\\puzzles\\puzzle1.txt";
    menu = new QMenu;
    menu->addAction("Set to 0");
    menu->addAction("Set to 1");
    menu->addAction("Set to 2");
    menu->addAction("Set to 3");
    menu->addAction("Set to 4");
    menu->addAction("Set to 5");
    menu->addAction("Set to 6");
    menu->addAction("Set to 7");
    menu->addAction("Set to 8");
    menu->addAction("Set to 9");
    menu->addSeparator();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FormulaShow()
{
    // scene
    scene = new QGraphicsScene();
    //scene->setSceneRect(0,0,750,550);



    // set backgroung image
    //setBackgroundBrush(QBrush(QImage(":/image/main_bg")));

   //
    formula_widget = new QWidget();
    formula_widget->setAttribute(Qt::WA_TranslucentBackground,true);
    //w->setFixedSize(500,500);

    PuzzleButton* btnuser;
    button_matrix = new PuzzleButton**[plus_formula->NK];
    for(int i = 0;i<plus_formula->NK;i++)
    {
         button_matrix[i] = new PuzzleButton*[plus_formula->N[i]];
    }
    QGraphicsProxyWidget *proxy;

    for(int i = 0;i<plus_formula->NK;i++)
    {
       for(int j = 0;j<plus_formula->N[i];j++)
       {
            button_matrix[i][j] = new PuzzleButton(formula_widget);
            button_matrix[i][j]->setGeometry(QRect(50*(1+plus_formula->N_Ans_Len - plus_formula->N_Add_LenMax) + 50*j,50*i,50,50));
           //btnuser->setText(QString(QString::number()));
            button_matrix[i][j]->setText(QString(plus_formula->Pointer_N[i][plus_formula->N[i] - j -1]->layout));
            button_matrix[i][j]->setMenu(menu);
       }
       if(i == plus_formula->NK -1)
       {
           btnuser = new PuzzleButton(formula_widget);
           btnuser->setGeometry(QRect(0,50*i,50,50));
           btnuser->setText("+");
       }
    }
    line = new QGraphicsLineItem(0,plus_formula->NK * 50 +25,(plus_formula->N_Ans_Len+1)*50,plus_formula->NK * 50+25);
    QPen _Pen;
    _Pen.setColor(Qt::white);
    _Pen.setWidth(3);
    line->setPen(_Pen);
    scene->addItem(line);
    for(int i = 0;i<plus_formula->N_Ans_Len;i++)
    {
        btnuser = new PuzzleButton(formula_widget);
        btnuser->setGeometry(QRect(50 + 50*i,50*(plus_formula->NK + 1),50,50));
        btnuser->setText(QString(plus_formula->Pointer_Ans[plus_formula->N_Ans_Len - i -1]->layout));
    }


    btnuser->setMenu(menu);

    proxy = scene->addWidget(formula_widget);

    // proxy->hide();

    // view *Game inherits View*
    ui->graphicsView->setGeometry(20,20,800,600);
    ui->graphicsView->setScene(scene);
    //this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->resize(800,600);
    this->setFixedSize(1080,720);

}
void MainWindow::FormulaPlusRead()
{
    ifstream fin(file_path);

    string *str_in;
    string str_ans;
    int k = 0;

    fin >> k;
    str_in = new string[k];
    for (int i = 0; i < k; i++)
    {
        fin >> str_in[i];
    }
    fin >> str_ans;

    plus_formula  = new formula(str_in,str_ans,k);
    plus_formula->plus_track_recursion();
//    for(int i = 0;i<plus_formula->symbol_num;i++)
//    {
//        cout <<plus_formula->result[i].layout<<"-"<< plus_formula->answer[0][i]<<endl;
//    }
}

void MainWindow::on_Button0_clicked()
{
    FormulaShow();
}
