#include "check_right_dialog.h"
#include "ui_check_right_dialog.h"

Check_Right_Dialog::Check_Right_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Check_Right_Dialog)
{
    ui->setupUi(this);
}

Check_Right_Dialog::~Check_Right_Dialog()
{
    delete ui;
}
