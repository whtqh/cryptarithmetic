#ifndef CHECK_RIGHT_DIALOG_H
#define CHECK_RIGHT_DIALOG_H

#include <QDialog>

namespace Ui {
class Check_Right_Dialog;
}

class Check_Right_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Check_Right_Dialog(QWidget *parent = 0);
    ~Check_Right_Dialog();

private:
    Ui::Check_Right_Dialog *ui;
};

#endif // CHECK_RIGHT_DIALOG_H
