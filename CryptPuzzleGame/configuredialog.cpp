#include "configuredialog.h"
#include "ui_configuredialog.h"
#include "mainwindow.h"
#include <sstream>
ConfigureDialog::ConfigureDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigureDialog)
{
    ui->setupUi(this);

}

ConfigureDialog::~ConfigureDialog()
{
    delete ui;
}

void ConfigureDialog::on_buttonBox_accepted()
{
     MainWindow* pointer = (MainWindow*)this->parentWidget();
    if(*(pointer->formula_kind) != -1)
    {
        pointer->file_num = *(pointer->formula_kind);
        stringstream ss;
        ss << pointer->file_num;
        string str = ss.str();
        pointer->file_path = "..\\CryptPuzzleGame\\puzzles\\puzzle" +str+".txt";
        cout << *(pointer->formula_kind)<<endl;
        if(*(pointer->formula_kind) <5)
        {
            pointer->FormulaPlusRead();//暂时代替读题库
            pointer->FormulaShow();
        }
        else if(*(pointer->formula_kind) < 9)
        {
            pointer->Minus_FormulaPlusRead();
            pointer->Minus_FormulaShow();
        }
        else if(*(pointer->formula_kind) < 13)
        {
            pointer->Times_FormulaPlusRead();
            pointer->Times_FormulaShow();
        }
        else
        {
            pointer->Divid_FormulaPlusRead();
            pointer->Divid_FormulaShow();
        }


    }
}
void ConfigureDialog::on_pushButton_clicked()
{
    MainWindow* pointer = (MainWindow*)this->parentWidget();
    *(pointer->formula_kind) = 1;
    on_buttonBox_accepted();
    this->hide();
}


void ConfigureDialog::on_pushButton_2_clicked()
{
    MainWindow* pointer = (MainWindow*)this->parentWidget();
    *(pointer->formula_kind) = 2;
    on_buttonBox_accepted();
    this->hide();
}



void ConfigureDialog::on_pushButton_3_clicked()
{
    MainWindow* pointer = (MainWindow*)this->parentWidget();
    *(pointer->formula_kind) = 3;
    on_buttonBox_accepted();
    this->hide();
}

void ConfigureDialog::on_pushButton_4_clicked()
{
    MainWindow* pointer = (MainWindow*)this->parentWidget();
    *(pointer->formula_kind) = 4;
    on_buttonBox_accepted();
    this->hide();
}

void ConfigureDialog::on_pushButton_5_clicked()
{
    MainWindow* pointer = (MainWindow*)this->parentWidget();
    *(pointer->formula_kind) = 5;
    on_buttonBox_accepted();
    this->hide();
}

void ConfigureDialog::on_pushButton_6_clicked()
{
    MainWindow* pointer = (MainWindow*)this->parentWidget();
    *(pointer->formula_kind) = 6;
    on_buttonBox_accepted();
    this->hide();
}

void ConfigureDialog::on_pushButton_7_clicked()
{
    MainWindow* pointer = (MainWindow*)this->parentWidget();
    *(pointer->formula_kind) = 7;
    on_buttonBox_accepted();
    this->hide();
}

void ConfigureDialog::on_pushButton_8_clicked()
{
    MainWindow* pointer = (MainWindow*)this->parentWidget();
    *(pointer->formula_kind) = 8;
    on_buttonBox_accepted();
    this->hide();
}

void ConfigureDialog::on_pushButton_9_clicked()
{
    MainWindow* pointer = (MainWindow*)this->parentWidget();
    *(pointer->formula_kind) = 9;
    on_buttonBox_accepted();
    this->hide();
}

void ConfigureDialog::on_pushButton_10_clicked()
{
    MainWindow* pointer = (MainWindow*)this->parentWidget();
    *(pointer->formula_kind) = 10;
    on_buttonBox_accepted();
    this->hide();
}

void ConfigureDialog::on_pushButton_11_clicked()
{
    MainWindow* pointer = (MainWindow*)this->parentWidget();
    *(pointer->formula_kind) = 11;
    on_buttonBox_accepted();
    this->hide();
}

void ConfigureDialog::on_pushButton_12_clicked()
{
    MainWindow* pointer = (MainWindow*)this->parentWidget();
    *(pointer->formula_kind) = 12;
    on_buttonBox_accepted();
    this->hide();
}

void ConfigureDialog::on_pushButton_13_clicked()
{
    MainWindow* pointer = (MainWindow*)this->parentWidget();
    *(pointer->formula_kind) = 13;
    on_buttonBox_accepted();
    this->hide();
}

void ConfigureDialog::on_pushButton_14_clicked()
{
    MainWindow* pointer = (MainWindow*)this->parentWidget();
    *(pointer->formula_kind) = 14;
    on_buttonBox_accepted();
    this->hide();
}

void ConfigureDialog::on_pushButton_15_clicked()
{
    MainWindow* pointer = (MainWindow*)this->parentWidget();
    *(pointer->formula_kind) = 15;
    on_buttonBox_accepted();
    this->hide();
}

void ConfigureDialog::on_pushButton_16_clicked()
{
    MainWindow* pointer = (MainWindow*)this->parentWidget();
    *(pointer->formula_kind) = 16;
    on_buttonBox_accepted();
    this->hide();
}
