#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    file_num = 0;
    file_path = "..\\CryptPuzzleGame\\puzzles\\puzzle2.txt";



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
    button_matrix = new PuzzleButton**[plus_formula->NK + 1];
    for(int i = 0;i<plus_formula->NK;i++)
    {
         button_matrix[i] = new PuzzleButton*[plus_formula->N[i]];
    }
    button_matrix[plus_formula->NK] = new PuzzleButton*[plus_formula->N_Ans_Len];
    QGraphicsProxyWidget *proxy;

    for(int i = 0;i<plus_formula->NK;i++)
    {
       for(int j = 0;j<plus_formula->N[i];j++)
       {
            button_matrix[i][j] = new PuzzleButton(formula_widget,i,j);
            connect(button_matrix[i][j], SIGNAL (Num_Increase(int,int)), this, SLOT (Increase_Num(int,int)));
            button_matrix[i][j]->setGeometry(QRect(50*(1+plus_formula->N_Ans_Len - plus_formula->N[i]) + 50*j,50*i,50,50));
            button_matrix[i][j]->setText(QString(plus_formula->Pointer_N[i][plus_formula->N[i] - j -1]->layout));
            //button_matrix[i][j]->num = plus_formula->Pointer_N[i][j]->num;//Have Bugs
            button_matrix[i][j]->layout = plus_formula->Pointer_N[i][plus_formula->N[i] - j -1]->layout;
       }
       if(i == plus_formula->NK -1)
       {
           btnuser = new PuzzleButton(formula_widget,i,plus_formula->N[i]);
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
        button_matrix[plus_formula->NK][i] = new PuzzleButton(formula_widget,plus_formula->NK,i);
        connect(button_matrix[plus_formula->NK][i], SIGNAL (Num_Increase(int,int)), this, SLOT (Increase_Num(int,int)));
        button_matrix[plus_formula->NK][i]->setGeometry(QRect(50 + 50*i,50*(plus_formula->NK + 1),50,50));
        button_matrix[plus_formula->NK][i]->setText(QString(plus_formula->Pointer_Ans[plus_formula->N_Ans_Len - i -1]->layout));
        //button_matrix[plus_formula->NK][i]->setMenu(menu);
        //(button_matrix[plus_formula->NK][i])->num = (plus_formula->Pointer_Ans[plus_formula->N_Ans_Len - i -1])->num;
        (button_matrix[plus_formula->NK][i])->layout = (plus_formula->Pointer_Ans[plus_formula->N_Ans_Len - i -1])->layout;
    }

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
void MainWindow::FormulaMenuInitial()       //Check Answer
{
    char char_key[10] = {};
    bool check = true;
    for(int t = 0;t<10;t++)
    {
        char temp_c = ' ';
        for(int i = 0;i < plus_formula->NK;i++)
        {
            for(int j = 0;j<plus_formula->N[i];j++)
            {
                if(button_matrix[i][j]->num == t)
                {
                    if(temp_c == ' ')
                    {
                        temp_c = button_matrix[i][j]->layout;
                    }
                    else if(temp_c != button_matrix[i][j]->layout)
                    {
                        check = false;
                        break;
                    }
                }
                else if(button_matrix[i][j]->num == -1)
                {
                    check = false;
                    break;
                }
            }
            if(check == false)
                break;
         }
        if(check == false)
            break;

        for(int j = 0; j<plus_formula->N_Ans_Len;j++)
        {
            int i = plus_formula->NK;
            if(button_matrix[i][j]->num == t)
            {
                if(temp_c == ' ')
                {
                    temp_c = button_matrix[i][j]->layout;
                }
                else if(temp_c != button_matrix[i][j]->layout|| button_matrix[i][j]->num == -1)
                {
                    check = false;
                    break;
                }
            }
            else if(button_matrix[i][j]->num == -1)
            {
                check = false;
                break;
            }
            char_key[t] = temp_c;
        }
    }
    if(check == true)
    {
        for(int j = 0;j<plus_formula->answer_num;j++)
        {
            bool temp_check = true;
            for(int i = 0;i<10;i++)
            {
                if(char_key[i]!=' ')
                {

                    std::size_t found = plus_formula->symbol_layout.find(char_key[i]);
                    char debug = plus_formula->result[(int)found].layout;
                    int num = plus_formula->result[(int)found].num;


                        if(plus_formula->answer[0][(int)found]!= i&&found!=std::string::npos)
                        {
                            temp_check = false;
                            break;
                        }
                }
            }
            if(temp_check == true)
            {
                cout <<"success"<<endl;
                return;
            }
        }
    }

        cout << "Wrong Answer"<<endl;
        return;
}
void MainWindow::FormulaAnswerShow()    //Add up func
{
    if(plus_formula->answer_num >= 1)
    {
        for(int i = 0;i<plus_formula->NK;i++)
        {
           for(int j = 0;j<plus_formula->N[i];j++)
           {
               std::size_t found = plus_formula->symbol_layout.find(button_matrix[i][j]->layout);
               int temp_num = plus_formula->answer[0][(int)found];
               button_matrix[i][j]->setText(QString(QString::number(temp_num)));
           }
        }
        for(int i = 0;i<plus_formula->N_Ans_Len;i++)
        {
            std::size_t found = plus_formula->symbol_layout.find(button_matrix[plus_formula->NK][i]->layout);
            int temp_num = plus_formula->answer[0][(int)found];
            button_matrix[plus_formula->NK][i]->setText(QString(QString::number(temp_num)));;
        }
    }
    else
    {
        for(int i = 0;i<plus_formula->NK;i++)
        {
           for(int j = 0;j<plus_formula->N[i];j++)
           {
               button_matrix[i][j]->setText("*");
           }
        }
        for(int i = 0;i<plus_formula->N_Ans_Len;i++)
        {
            button_matrix[plus_formula->NK][i]->setText("*");;
        }
    }
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

void MainWindow::on_Button0_clicked()   //Show Problem
{
    FormulaShow();
}

void MainWindow::on_Button3_clicked()   //To Check Answer
{
    FormulaMenuInitial();
}

void MainWindow::on_Button4_clicked()   //To show answers
{
    FormulaAnswerShow();
}

void MainWindow::TestMenu()
{

    cout << "Fuck!"<<endl;
}

void MainWindow::Increase_Num(int m_i,int m_j)
{
    button_matrix[m_i][m_j]->num = (button_matrix[m_i][m_j]->num + 1)%10;
    button_matrix[m_i][m_j]->setText(QString(button_matrix[m_i][m_j]->layout)
                                 +"(" + QString(QString::number(button_matrix[m_i][m_j]->num)) + ")");
    button_matrix[m_i][m_j]->setStyleSheet("QPushButton { background-color: #214b3f;font-size: 12pt;font-weight: bold;color: #ffff00;}");

    for(int i = 0;i<plus_formula->NK;i++)
    {
        for(int j = 0;j<plus_formula->N[i];j++)
        {
            if(button_matrix[i][j]->layout == button_matrix[m_i][m_j]->layout&&(i!=m_i||j!=m_j))
            {
                button_matrix[i][j]->num = (button_matrix[i][j]->num + 1)%10;
                button_matrix[i][j]->setText(QString(button_matrix[i][j]->layout)
                                             +"(" + QString(QString::number(button_matrix[i][j]->num)) + ")");
                button_matrix[i][j]->setStyleSheet("QPushButton { background-color: #214b3f;font-size: 12pt;font-weight: bold;color: #ffff00;}");
            }
        }
    }
    for(int j = 0; j<plus_formula->N_Ans_Len;j++)
    {
        int i = plus_formula->NK;
        if(button_matrix[i][j]->layout == button_matrix[m_i][m_j]->layout&&(i!=m_i||j!=m_j))
        {
            button_matrix[i][j]->num = (button_matrix[i][j]->num + 1)%10;
            button_matrix[i][j]->setText(QString(button_matrix[i][j]->layout)
                                         +"(" + QString(QString::number(button_matrix[i][j]->num)) + ")");
            button_matrix[i][j]->setStyleSheet("QPushButton { background-color: #214b3f;font-size: 12pt;font-weight: bold;color: #ffff00;}");
        }
    }
}

