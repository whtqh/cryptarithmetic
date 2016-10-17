#ifndef CHECK_WRONG_DIALOG_H
#define CHECK_WRONG_DIALOG_H

#include <QDialog>

namespace Ui {
class Check_Wrong_Dialog;
}

class Check_Wrong_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Check_Wrong_Dialog(QWidget *parent = 0);
    ~Check_Wrong_Dialog();

private:
    Ui::Check_Wrong_Dialog *ui;
};

#endif // CHECK_WRONG_DIALOG_H
