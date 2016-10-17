#include "check_wrong_dialog.h"
#include "ui_check_wrong_dialog.h"

Check_Wrong_Dialog::Check_Wrong_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Check_Wrong_Dialog)
{
    ui->setupUi(this);
}

Check_Wrong_Dialog::~Check_Wrong_Dialog()
{
    delete ui;
}
