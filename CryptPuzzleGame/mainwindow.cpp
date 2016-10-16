#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    FormulaShow();
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
    //scene->addLine(0,75,500,75);

    //scene->addText(tr("中国"));

    // set backgroung image
    //setBackgroundBrush(QBrush(QImage(":/bg-images/bg-image.png")));

   //
    formula = new QWidget();
    formula->setAttribute(Qt::WA_TranslucentBackground,true);
    //w->setFixedSize(500,500);
    PuzzleButton* btnuser;
    QGraphicsProxyWidget *proxy;

    for(int i = 0;i<5;i++)
    {
       for(int j = 0;j<5;j++)
       {
           btnuser = new PuzzleButton(formula);
           btnuser->setMinimumSize(50,50);
           btnuser->setStyleSheet("QPushButton { background-color: #ffffff;font-size: 26pt;font-weight: bold;} \
                                   QPushButton:hover{background-color: blue;}  \
                                  QPushButton:pressed{background-color: red;}");
           btnuser->setGeometry(QRect(60*i,60*j,50,50));
           btnuser->setText("马");
           QFont font = btnuser->font();
          // font.setPointSize(30);
           btnuser->setFont(font);
       }
    }
    proxy = scene->addWidget(formula);


    // view *Game inherits View*
    ui->graphicsView->setGeometry(50,50,800,600);
    ui->graphicsView->setScene(scene);
    //this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->resize(800,600);
    this->setFixedSize(1080,720);

}
