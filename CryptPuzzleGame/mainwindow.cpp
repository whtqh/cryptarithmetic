#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    formula_kind = new int;
    *formula_kind = -1;
    file_num = 0;
    file_path = "..\\CryptPuzzleGame\\puzzles\\puzzle1.txt";



}

MainWindow::~MainWindow()
{
    delete ui;
}
//Plus Function---------------------------------------------------------
void MainWindow::FormulaPlusRead()  //读题库文件
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
}
void MainWindow::FormulaShow()  //将从题库中读出的数据展示出来
{
    // scene
    scene = new QGraphicsScene();
    //scene->setSceneRect(0,0,750,550);

    formula_widget = new QWidget();
    formula_widget->setAttribute(Qt::WA_TranslucentBackground,true);

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
//                    char debug = plus_formula->result[(int)found].layout;
//                    int num = plus_formula->result[(int)found].num;


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
                Ans_Right = new Check_Right_Dialog(this);
                Ans_Right->show();
                return;
            }
        }
    }

        cout << "Wrong Answer"<<endl;
        Ans_Wrong = new Check_Wrong_Dialog(this);
        Ans_Wrong->show();
        return;
}
void MainWindow::FormulaAnswerShow()    //Add up func
{
    //需要输出当前一共有几个解的信息
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
//+-*/ is all the same

//Minus Function--------------------------------------------------------
void MainWindow::Minus_FormulaPlusRead()     //Show Problem
{
    ifstream fin(file_path);

    string *str_in;
    string str_ans;

    str_in = new string[2];

    fin >> str_ans;
    fin >> str_in[0];
    fin >> str_in[1];

    mins_formula = new minus_formula(str_ans, str_in);
    mins_formula->minus_track_recursion();
}

void MainWindow::Minus_FormulaShow()        //To show the problem
{
    // scene
    scene = new QGraphicsScene();
    //scene->setSceneRect(0,0,750,550);

    formula_widget = new QWidget();
    formula_widget->setAttribute(Qt::WA_TranslucentBackground,true);

    PuzzleButton* btnuser;
    button_matrix = new PuzzleButton**[3];
    button_matrix[2] = new PuzzleButton*[mins_formula->add_formula.N_Ans_Len];
    button_matrix[0] = new PuzzleButton*[mins_formula->add_formula.N[0]];
    button_matrix[1] = new PuzzleButton*[mins_formula->add_formula.N[1]];

    QGraphicsProxyWidget *proxy;


    for(int i = 0;i<mins_formula->add_formula.N_Ans_Len;i++)
    {
        button_matrix[2][i] = new PuzzleButton(formula_widget,0,i);
        connect(button_matrix[2][i], SIGNAL (Num_Increase(int,int)), this, SLOT (Increase_Num(int,int)));
        button_matrix[2][i]->setGeometry(QRect(50 + 50*i,50*0,50,50));
        button_matrix[2][i]->setText(QString(mins_formula->add_formula.Pointer_Ans[mins_formula->add_formula.N_Ans_Len - i -1]->layout));
        //button_matrix[2][i]->setMenu(menu);
        //(button_matrix[2][i])->num = (mins_formula->add_formula.Pointer_Ans[mins_formula->add_formula.N_Ans_Len - i -1])->num;
        (button_matrix[2][i])->layout = (mins_formula->add_formula.Pointer_Ans[mins_formula->add_formula.N_Ans_Len - i -1])->layout;
    }
    int i = 0;
    for(int j = 0;j<mins_formula->add_formula.N[i];j++)
    {
        button_matrix[0][j] = new PuzzleButton(formula_widget,1,j);
        connect(button_matrix[0][j], SIGNAL (Num_Increase(int,int)), this, SLOT (Increase_Num(int,int)));
        button_matrix[0][j]->setGeometry(QRect(50*(1+mins_formula->add_formula.N_Ans_Len - mins_formula->add_formula.N[i]) + 50*j,50,50,50));
        button_matrix[0][j]->setText(QString(mins_formula->add_formula.Pointer_N[i][mins_formula->add_formula.N[i] - j -1]->layout));
        //button_matrix[0][j]->num = mins_formula->add_formula.Pointer_N[i][j]->num;//Have Bugs
        button_matrix[0][j]->layout = mins_formula->add_formula.Pointer_N[i][mins_formula->add_formula.N[i] - j -1]->layout;
    }

    btnuser = new PuzzleButton(formula_widget,i,mins_formula->add_formula.N[i]);
    btnuser->setGeometry(QRect(0,50,50,50));
    btnuser->setText("-");


    line = new QGraphicsLineItem(0,2 * 50 +25,(mins_formula->add_formula.N_Ans_Len+1)*50,2 * 50+25);
    QPen _Pen;
    _Pen.setColor(Qt::white);
    _Pen.setWidth(3);
    line->setPen(_Pen);
    scene->addItem(line);

    i = 1;
    for(int j = 0;j<mins_formula->add_formula.N[i];j++)
    {
        button_matrix[1][j] = new PuzzleButton(formula_widget,2,j);
        connect(button_matrix[1][j], SIGNAL (Num_Increase(int,int)), this, SLOT (Increase_Num(int,int)));
        button_matrix[1][j]->setGeometry(QRect(50*(1+mins_formula->add_formula.N_Ans_Len - mins_formula->add_formula.N[i]) + 50*j,50*3,50,50));
        button_matrix[1][j]->setText(QString(mins_formula->add_formula.Pointer_N[i][mins_formula->add_formula.N[i] - j -1]->layout));
        //button_matrix[1][j]->num = mins_formula->add_formula.Pointer_N[i][j]->num;//Have Bugs
        button_matrix[1][j]->layout = mins_formula->add_formula.Pointer_N[i][mins_formula->add_formula.N[i] - j -1]->layout;
    }
     proxy = scene->addWidget(formula_widget);
    // view *Game inherits View*
    ui->graphicsView->setGeometry(20,20,800,600);
    ui->graphicsView->setScene(scene);
    //this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->resize(800,600);
    this->setFixedSize(1080,720);
}

void MainWindow::Minus_FormulaMenuInitial()  //To Check problem
{

}

void MainWindow::Minus_FormulaAnswerShow()   //To show the answers
{
    if(mins_formula->add_formula.answer_num >= 1)
    {
        for(int i = 0;i<2;i++)
        {
           for(int j = 0;j<mins_formula->add_formula.N[i];j++)
           {
               std::size_t found = mins_formula->add_formula.symbol_layout.find(button_matrix[i][j]->layout);
               int temp_num = mins_formula->add_formula.answer[0][(int)found];
               button_matrix[i][j]->setText(QString(QString::number(temp_num)));
           }
        }
        for(int i = 0;i<mins_formula->add_formula.N_Ans_Len;i++)
        {
            std::size_t found = mins_formula->add_formula.symbol_layout.find(button_matrix[2][i]->layout);
            int temp_num = mins_formula->add_formula.answer[0][(int)found];
            button_matrix[2][i]->setText(QString(QString::number(temp_num)));;
        }
    }
    else
    {
        for(int i = 0;i<2;i++)
        {
           for(int j = 0;j<mins_formula->add_formula.N[i];j++)
           {
               button_matrix[i][j]->setText("*");
           }
        }
        for(int i = 2;i<mins_formula->add_formula.N_Ans_Len;i++)
        {
            button_matrix[2][i]->setText("*");;
        }
    }

}

//tims Func--------------------------------------------------
void MainWindow::Times_FormulaPlusRead()     //Show Problem
{
    ifstream fin(file_path);
    string str_up;
    string str_down;
    string *str_in;//using c_str() while printf
    string str_ans;
    int k = 0;
    //cout << "input times formula's str_up & str_down" << endl;
    fin >> str_up;
    fin >> str_down;
    //cout << "input str_in one by one" << endl;
    k = str_down.size();
    str_in = new string[k];
    for (int i = 0; i < k; i++)
    {
        string str_temp;
        fin >> str_temp;
        for (int j = 0; j < i; j++)
        {
            str_temp = str_temp + '0';
        }
        str_in[i] = str_temp;
    }

    //cout << "input str_ans " << endl;
    fin >> str_ans;


    tims_formula = new times_formula(str_up, str_down, str_in, str_ans);
    tims_formula->times_track_recurison();
}
void MainWindow::Times_FormulaShow()         //To show the problem
{
    // scene
    scene = new QGraphicsScene();
    //scene->setSceneRect(0,0,750,550);

    formula_widget = new QWidget();
    formula_widget->setAttribute(Qt::WA_TranslucentBackground,true);

    PuzzleButton* btnuser;
    button_matrix = new PuzzleButton**[tims_formula->NK + 3];       // +3

    button_matrix[0] = new PuzzleButton*[tims_formula->N_Multi_Up_Len];
    button_matrix[1] = new PuzzleButton*[tims_formula->N_Multi_Down_Len];
    for(int i = 0;i<tims_formula->NK;i++)
    {
         button_matrix[i+2] = new PuzzleButton*[tims_formula->N[i]];
    }
    button_matrix[tims_formula->NK+2] = new PuzzleButton*[tims_formula->N_Ans_Len];

    QGraphicsProxyWidget *proxy;
    for(int j = 0;j<tims_formula->N_Multi_Up_Len;j++)
    {
        button_matrix[0][j] = new PuzzleButton(formula_widget,0,j);
        connect(button_matrix[0][j], SIGNAL (Num_Increase(int,int)), this, SLOT (Increase_Num(int,int)));
        button_matrix[0][j]->setGeometry(QRect(50*(1+tims_formula->N_Ans_Len - tims_formula->N_Multi_Up_Len) + 50*j,50*0,50,50));
        button_matrix[0][j]->setText(QString(tims_formula->Pointer_Up[tims_formula->N_Multi_Up_Len - j -1]->layout));
        //button_matrix[0][j]->num = tims_formula->Pointer_N[i][j]->num;//Have Bugs
        button_matrix[0][j]->layout = tims_formula->Pointer_Up[tims_formula->N_Multi_Up_Len - j -1]->layout;
    }
    for(int j = 0;j<tims_formula->N_Multi_Down_Len;j++)
    {
        button_matrix[1][j] = new PuzzleButton(formula_widget,1,j);
        connect(button_matrix[1][j], SIGNAL (Num_Increase(int,int)), this, SLOT (Increase_Num(int,int)));
        button_matrix[1][j]->setGeometry(QRect(50*(1+tims_formula->N_Ans_Len - tims_formula->N_Multi_Down_Len) + 50*j,50*1,50,50));
        button_matrix[1][j]->setText(QString(tims_formula->Pointer_Down[tims_formula->N_Multi_Down_Len - j -1]->layout));
        //button_matrix[1][j]->num = tims_formula->Pointer_N[i][j]->num;//Have Bugs
        button_matrix[1][j]->layout = tims_formula->Pointer_Down[tims_formula->N_Multi_Down_Len - j -1]->layout;
    }

   btnuser = new PuzzleButton(formula_widget,1,tims_formula->N_Multi_Down_Len);
   btnuser->setGeometry(QRect(0,50,50,50));
   btnuser->setText("X");

    for(int i = 0;i<tims_formula->NK;i++)
    {
       for(int j = 0;j<tims_formula->N[i] - i;j++)
       {
            button_matrix[i+2][j] = new PuzzleButton(formula_widget,i+2,j);
            connect(button_matrix[i+2][j], SIGNAL (Num_Increase(int,int)), this, SLOT (Increase_Num(int,int)));
            button_matrix[i+2][j]->setGeometry(QRect(50*(1+tims_formula->N_Ans_Len - tims_formula->N[i]) + 50*j,50*(i+3),50,50));
            button_matrix[i+2][j]->setText(QString(tims_formula->Pointer_N[i][tims_formula->N[i] - j -1]->layout));
            //button_matrix[i+2][j]->num = tims_formula->Pointer_N[i][j]->num;//Have Bugs
            button_matrix[i+2][j]->layout = tims_formula->Pointer_N[i][tims_formula->N[i] - j -1]->layout;
       }

    }
    line = new QGraphicsLineItem(0,2 * 50 +25,(tims_formula->N_Ans_Len+1)*50,2 * 50+25);
    QPen _Pen;
    _Pen.setColor(Qt::white);
    _Pen.setWidth(3);
    line->setPen(_Pen);
    scene->addItem(line);
    for(int i = 0;i<tims_formula->N_Ans_Len;i++)
    {
        button_matrix[tims_formula->NK+2][i] = new PuzzleButton(formula_widget,tims_formula->NK+2,i);
        connect(button_matrix[tims_formula->NK+2][i], SIGNAL (Num_Increase(int,int)), this, SLOT (Increase_Num(int,int)));
        button_matrix[tims_formula->NK+2][i]->setGeometry(QRect(50 + 50*i,50*(tims_formula->NK + 4),50,50));
        button_matrix[tims_formula->NK+2][i]->setText(QString(tims_formula->Pointer_Ans[tims_formula->N_Ans_Len - i -1]->layout));
        //button_matrix[tims_formula->NK+2][i]->setMenu(menu);
        //(button_matrix[tims_formula->NK+2][i])->num = (tims_formula->Pointer_Ans[tims_formula->N_Ans_Len - i -1])->num;
        (button_matrix[tims_formula->NK+2][i])->layout = (tims_formula->Pointer_Ans[tims_formula->N_Ans_Len - i -1])->layout;
    }
    line = new QGraphicsLineItem(0,(tims_formula->NK +3) * 50 +25,(tims_formula->N_Ans_Len+1)*50,(tims_formula->NK +3) * 50+25);
    //QPen _Pen;
    _Pen.setColor(Qt::white);
    _Pen.setWidth(3);
    line->setPen(_Pen);
    scene->addItem(line);
    proxy = scene->addWidget(formula_widget);
    // view *Game inherits View*
    ui->graphicsView->setGeometry(20,20,800,600);
    ui->graphicsView->setScene(scene);
    //this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->resize(800,600);
    this->setFixedSize(1080,720);
}
void MainWindow::Times_FormulaMenuInitial()  //To Check problem
{

}
void MainWindow::Times_FormulaAnswerShow()   //To show the answers
{
    if(tims_formula->answer_num >= 1)
    {
        for(int i = 0;i<tims_formula->NK;i++)
        {
           for(int j = 0;j<tims_formula->N[i] - i;j++)
           {
               std::size_t found = tims_formula->symbol_layout.find(button_matrix[i+2][j]->layout);
               int temp_num = tims_formula->answer[0][(int)found];
               button_matrix[i+2][j]->setText(QString(QString::number(temp_num)));
           }
        }
        for(int i = 0;i<tims_formula->N_Ans_Len;i++)
        {
            std::size_t found = tims_formula->symbol_layout.find(button_matrix[tims_formula->NK + 2][i]->layout);
            int temp_num = tims_formula->answer[0][(int)found];
            button_matrix[tims_formula->NK + 2][i]->setText(QString(QString::number(temp_num)));;
        }
        for(int i = 0;i<tims_formula->N_Multi_Up_Len;i++)
        {
            std::size_t found = tims_formula->symbol_layout.find(button_matrix[0][i]->layout);
            int temp_num = tims_formula->answer[0][(int)found];
            button_matrix[0][i]->setText(QString(QString::number(temp_num)));;
        }
        for(int i = 0;i<tims_formula->N_Multi_Down_Len;i++)
        {
            std::size_t found = tims_formula->symbol_layout.find(button_matrix[1][i]->layout);
            int temp_num = tims_formula->answer[0][(int)found];
            button_matrix[1][i]->setText(QString(QString::number(temp_num)));;
        }
    }
    else
    {
        for(int i = 0;i<tims_formula->NK;i++)
        {
           for(int j = 0;j<tims_formula->N[i] - i;j++)
           {
               button_matrix[i+2][j]->setText("*");
           }
        }
        for(int i = 0;i<tims_formula->N_Ans_Len;i++)
        {
            button_matrix[tims_formula->NK + 2][i]->setText("*");;
        }
        for(int i = 0;i<tims_formula->N_Multi_Up_Len;i++)
        {
            button_matrix[0][i]->setText("*");;
        }
        for(int i = 0;i<tims_formula->N_Multi_Down_Len;i++)
        {
            button_matrix[1][i]->setText("*");;
        }
    }
}

//divd Func--------------------------------------------------
void MainWindow::Divid_FormulaPlusRead()     //Show Problem
{
    ifstream fin(file_path);
    string str_up;
    string str_down;
    string *str_in;//using c_str() while printf
    string *str_remain;
    string str_ans;
    int k = 0;

    //cout << "input dividid formula's str_up & str_down" << endl;
    fin >> str_up;
    fin >> str_down;
    //cout << "input str_in one by one" << endl;
    k = str_down.size();
    str_in = new string[k];
    str_remain = new string[k];
    for (int i = k-1; i >= 0; i--)
    {
        string str_temp;

        //Add up
        fin >> str_temp;
        for (int j = 0; j < i; j++)
        {
            str_temp = str_temp + '0';
        }
        str_in[i] = str_temp;

        //Remainder
        fin >> str_temp;
        for (int j = 1; j < i; j++)	//Less one '0'
        {
            str_temp = str_temp + '0';
        }
        str_remain[i] = str_temp;
    }

    //cout << "input str_ans " << endl;
    fin >> str_ans;
    divd_formula = new divide_formula(str_up, str_down, str_in, str_remain, str_ans);
    divd_formula->divide_track_recurison();
}
void MainWindow::Divid_FormulaShow()         //To show the problem
{

    // scene
    scene = new QGraphicsScene();
    //scene->setSceneRect(0,0,750,550);

    formula_widget = new QWidget();
    formula_widget->setAttribute(Qt::WA_TranslucentBackground,true);

    PuzzleButton* btnuser;
    button_matrix = new PuzzleButton**[divd_formula->NK * 2  + 2];       // +3

    button_matrix[0] = new PuzzleButton*[divd_formula->N_Multi_Down_Len];
    button_matrix[1] = new PuzzleButton*[divd_formula->N_Multi_Up_Len + divd_formula->N_Ans_Len +1];
    for(int i = 0;i<divd_formula->NK;i++)
    {
         button_matrix[i*2+2] = new PuzzleButton*[divd_formula->N[i]];
    }
    for(int i = 0;i<divd_formula->NK;i++)
    {
         button_matrix[i*2+3] = new PuzzleButton*[divd_formula->R[i]];
    }
    QGraphicsProxyWidget *proxy;
    //i = 0
    for(int j = 0;j<divd_formula->N_Multi_Down_Len;j++)
    {
        button_matrix[0][j] = new PuzzleButton(formula_widget,0,j);
        connect(button_matrix[0][j], SIGNAL (Num_Increase(int,int)), this, SLOT (Increase_Num(int,int)));
        button_matrix[0][j]->setGeometry(QRect(50*(1+divd_formula->N_Ans_Len + divd_formula->N_Multi_Up_Len- divd_formula->N_Multi_Down_Len) + 50*j,50*0,50,50));
        button_matrix[0][j]->setText(QString(divd_formula->Pointer_Down[divd_formula->N_Multi_Down_Len - j -1]->layout));
        //button_matrix[0][j]->num = divd_formula->Pointer_N[i][j]->num;//Have Bugs
        button_matrix[0][j]->layout = divd_formula->Pointer_Down[divd_formula->N_Multi_Down_Len - j -1]->layout;
    }

    line = new QGraphicsLineItem((divd_formula->N_Multi_Up_Len +1)*50, 50 +25,(divd_formula->N_Multi_Up_Len +divd_formula->N_Ans_Len+1)*50,50+25);
    QPen _Pen;
    _Pen.setColor(Qt::white);
    _Pen.setWidth(3);
    line->setPen(_Pen);
    scene->addItem(line);

    line = new QGraphicsLineItem((divd_formula->N_Multi_Up_Len +1)*50, 50 +25,(divd_formula->N_Multi_Up_Len +1)*50 - 25,50*3);
    line->setPen(_Pen);
    scene->addItem(line);

    //i = 1
    for(int j = 0;j<divd_formula->N_Multi_Up_Len + divd_formula->N_Ans_Len +1;j++)
    {

        if(j == divd_formula->N_Multi_Up_Len)
        {
            continue;
        }
        button_matrix[1][j] = new PuzzleButton(formula_widget,1,j);
        connect(button_matrix[1][j], SIGNAL (Num_Increase(int,int)), this, SLOT (Increase_Num(int,int)));
        button_matrix[1][j]->setGeometry(QRect(50*j,50*2,50,50));
        if(j < divd_formula->N_Multi_Up_Len)
        {
            button_matrix[1][j]->setText(QString(divd_formula->Pointer_Up[divd_formula->N_Multi_Up_Len - j -1]->layout));
            button_matrix[1][j]->layout = divd_formula->Pointer_Up[divd_formula->N_Multi_Up_Len - j -1]->layout;
        }
        else
        {
            button_matrix[1][j]->setText(QString(divd_formula->Pointer_Ans[divd_formula->N_Ans_Len + divd_formula->N_Multi_Up_Len - j]->layout));
            button_matrix[1][j]->layout = divd_formula->Pointer_Ans[divd_formula->N_Ans_Len +divd_formula->N_Multi_Up_Len - j]->layout;
        }
    }


    for(int i = 0;i<divd_formula->NK ;i++)
    {
        //i = i*2+2
        for(int j = 0;j<divd_formula->N[divd_formula->NK - i -1] - (divd_formula->NK - i -1)  ;j++)
        {
             button_matrix[i*2+2][j] = new PuzzleButton(formula_widget,i*2+2,j);
             connect(button_matrix[i*2+2][j], SIGNAL (Num_Increase(int,int)), this, SLOT (Increase_Num(int,int)));
             button_matrix[i*2+2][j]->setGeometry(QRect(50*(divd_formula->N_Multi_Up_Len + 1) +50*(j + i) ,50*(3*i+3),50,50));
             button_matrix[i*2+2][j]->setText(QString(divd_formula->Pointer_N[divd_formula->NK - i -1][divd_formula->N[divd_formula->NK - i -1] - j -1]->layout));
             //button_matrix[i+2][j]->num = divd_formula->Pointer_N[i][j]->num;//Have Bugs
             button_matrix[i*2+2][j]->layout = divd_formula->Pointer_N[divd_formula->NK - i -1][divd_formula->N[divd_formula->NK - i -1] - j -1]->layout;
        }

        line = new QGraphicsLineItem(50*(divd_formula->N_Multi_Up_Len + 1) +50*i , 50*(3*i+4) + 25,50*(divd_formula->N_Multi_Up_Len + 2) +50*(divd_formula->R[divd_formula->NK - i -1] - (divd_formula->NK - i -1) + i) ,50*(3*i+4) + 25);
        line->setPen(_Pen);
        scene->addItem(line);

       if(i!= (divd_formula->NK -1))
       {
            //i = i*2+3
           for(int j = 0;j<divd_formula->R[divd_formula->NK - i -1] - (divd_formula->NK - i -1)+1  ;j++)
           {

                button_matrix[i*2+3][j] = new PuzzleButton(formula_widget,i*2+3,j);
                connect(button_matrix[i*2+3][j], SIGNAL (Num_Increase(int,int)), this, SLOT (Increase_Num(int,int)));
                button_matrix[i*2+3][j]->setGeometry(QRect(50*(divd_formula->N_Multi_Up_Len + 2) +50*(j + i) ,50*(3*i+5),50,50));
                button_matrix[i*2+3][j]->setText(QString(divd_formula->Pointer_R[divd_formula->NK - i -1][divd_formula->R[divd_formula->NK - i -1] - j -1]->layout));
                //button_matrix[i+2][j]->num = divd_formula->Pointer_R[i][j]->num;//Have Bugs
                button_matrix[i*2+3][j]->layout = divd_formula->Pointer_R[divd_formula->NK - i -1][divd_formula->R[divd_formula->NK - i -1] - j -1]->layout;
           }
       }
       else
       {
            //i = i*2+3
           for(int j = 0;j<divd_formula->R[divd_formula->NK - i -1] - (divd_formula->NK - i -1)  ;j++)
           {

                button_matrix[i*2+3][j] = new PuzzleButton(formula_widget,i*2+3,j);
                connect(button_matrix[i*2+3][j], SIGNAL (Num_Increase(int,int)), this, SLOT (Increase_Num(int,int)));
                button_matrix[i*2+3][j]->setGeometry(QRect(50*(divd_formula->N_Multi_Up_Len + 2) +50*(j + i) ,50*(3*i+5),50,50));
                button_matrix[i*2+3][j]->setText(QString(divd_formula->Pointer_R[divd_formula->NK - i -1][divd_formula->R[divd_formula->NK - i -1] - j -1]->layout));
                //button_matrix[i+2][j]->num = divd_formula->Pointer_R[i][j]->num;//Have Bugs
                button_matrix[i*2+3][j]->layout = divd_formula->Pointer_R[divd_formula->NK - i -1][divd_formula->R[divd_formula->NK - i -1] - j -1]->layout;
           }
       }

    }


    proxy = scene->addWidget(formula_widget);
    // view *Game inherits View*
    ui->graphicsView->setGeometry(20,20,800,600);
    ui->graphicsView->setScene(scene);

    ui->graphicsView->resize(800,600);
    this->setFixedSize(1080,720);
}

void MainWindow::Divid_FormulaMenuInitial()  //To Check problem
{

}

void MainWindow::Divid_FormulaAnswerShow()   //To show the answers
{
    if(divd_formula->answer_num >= 1)
    {
        for(int i = 0;i<divd_formula->NK;i++)
        {
           for(int j = 0;j<divd_formula->N[i] - i;j++)
           {
               std::size_t found = divd_formula->symbol_layout.find(button_matrix[2*i+2][j]->layout);
               int temp_num = divd_formula->answer[0][(int)found];
               button_matrix[2*i+2][j]->setText(QString(QString::number(temp_num)));
           }
        }
        for(int i = 0;i<divd_formula->NK-1;i++)
        {
           for(int j = 0;j<divd_formula->R[divd_formula->NK - i -1] - (divd_formula->NK - i -1) +1;j++)
           {
               std::size_t found = divd_formula->symbol_layout.find(button_matrix[2*i+3][j]->layout);
               int temp_num = divd_formula->answer[0][(int)found];
               button_matrix[2*i+3][j]->setText(QString(QString::number(temp_num)));
           }
        }
        for(int i = 0;i<divd_formula->N_Multi_Down_Len;i++)
        {
            std::size_t found = divd_formula->symbol_layout.find(button_matrix[0][i]->layout);
            int temp_num = divd_formula->answer[0][(int)found];
            button_matrix[0][i]->setText(QString(QString::number(temp_num)));
        }
        for(int i = 0;i<divd_formula->N_Multi_Up_Len + divd_formula->N_Ans_Len +1;i++)
        {
            if(i == divd_formula->N_Multi_Up_Len)
                continue;
            std::size_t found = divd_formula->symbol_layout.find(button_matrix[1][i]->layout);
            int temp_num = divd_formula->answer[0][(int)found];
            button_matrix[1][i]->setText(QString(QString::number(temp_num)));
        }

    }
    else
    {
        for(int i = 0;i<divd_formula->NK;i++)
        {
           for(int j = 0;j<divd_formula->N[i] - i;j++)
           {
               button_matrix[2*i+2][j]->setText("*");
           }
        }
        for(int i = 0;i<divd_formula->NK-1;i++)
        {
           for(int j = 0;j<divd_formula->R[divd_formula->NK - i -1] - (divd_formula->NK - i -1) +1;j++)
           {
               button_matrix[2*i+3][j]->setText("*");
           }
        }
        for(int i = 0;i<divd_formula->N_Multi_Down_Len;i++)
        {
            button_matrix[0][i]->setText("*");
        }
        for(int i = 0;i<divd_formula->N_Multi_Up_Len + divd_formula->N_Ans_Len +1;i++)
        {
            if(i == divd_formula->N_Multi_Up_Len)
                continue;
            button_matrix[1][i]->setText("*");;
        }
    }
}



void MainWindow::on_Button0_clicked()   //Show Problem      前提是已经读取到数据
{

    QuestionBase = new ConfigureDialog(this);
    QuestionBase->show();


}
void MainWindow::on_Button3_clicked()   //To Check Answer   检查当前的答案是否正确
{
    if(*(formula_kind) <5)
    {
        FormulaMenuInitial();
    }
}
void MainWindow::on_Button4_clicked()   //To show answers   显示当前加法的答案
{
    if(*(formula_kind) <5)
    {
        FormulaAnswerShow();
    }
    else if(*(formula_kind) < 9)
    {
        Minus_FormulaAnswerShow();
    }
    else if(*(formula_kind) < 13)
    {
        Times_FormulaAnswerShow();
    }
    else
    {
        Divid_FormulaAnswerShow();
    }
}


void MainWindow::TestMenu()
{

    cout << "test!"<<endl;
}

void MainWindow::Increase_Num(int m_i,int m_j)
{
    if(*(formula_kind) <5)
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
    return;
}

