/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QProgressBar *progressBar;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *Button0;
    QPushButton *Button1;
    QPushButton *Button2;
    QPushButton *Button3;
    QPushButton *Button4;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *Button_clear;
    QPushButton *Button_quit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1080, 720);
        MainWindow->setMinimumSize(QSize(1080, 720));
        MainWindow->setStyleSheet(QStringLiteral("background-image: url(:/image/window_bg);"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(21, 21, 800, 600));
        graphicsView->setMinimumSize(QSize(800, 600));
        graphicsView->setStyleSheet(QStringLiteral("background-image: url(:/image/main_bg);"));
        graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(20, 660, 841, 23));
        progressBar->setValue(0);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(850, 20, 201, 530));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Button0 = new QPushButton(layoutWidget);
        Button0->setObjectName(QStringLiteral("Button0"));
        Button0->setMinimumSize(QSize(160, 100));
        Button0->setStyleSheet(QStringLiteral("background-image: url(:/image/button_01);"));

        verticalLayout->addWidget(Button0);

        Button1 = new QPushButton(layoutWidget);
        Button1->setObjectName(QStringLiteral("Button1"));
        Button1->setMinimumSize(QSize(160, 100));
        Button1->setStyleSheet(QStringLiteral("background-image: url(:/image/button_02);"));

        verticalLayout->addWidget(Button1);

        Button2 = new QPushButton(layoutWidget);
        Button2->setObjectName(QStringLiteral("Button2"));
        Button2->setMinimumSize(QSize(160, 100));
        Button2->setStyleSheet(QStringLiteral("background-image: url(:/image/button_03);"));

        verticalLayout->addWidget(Button2);

        Button3 = new QPushButton(layoutWidget);
        Button3->setObjectName(QStringLiteral("Button3"));
        Button3->setMinimumSize(QSize(160, 100));
        Button3->setStyleSheet(QLatin1String("background-image: url(:/image/button_04);\n"
""));

        verticalLayout->addWidget(Button3);

        Button4 = new QPushButton(layoutWidget);
        Button4->setObjectName(QStringLiteral("Button4"));
        Button4->setMinimumSize(QSize(160, 100));
        Button4->setStyleSheet(QStringLiteral("background-image: url(:/image/button_05);"));
        Button4->setFlat(false);

        verticalLayout->addWidget(Button4);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(850, 560, 199, 62));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Button_clear = new QPushButton(layoutWidget1);
        Button_clear->setObjectName(QStringLiteral("Button_clear"));
        Button_clear->setMinimumSize(QSize(95, 60));
        Button_clear->setStyleSheet(QStringLiteral("background-image: url(:/image/button_clear);"));
        Button_clear->setFlat(false);

        horizontalLayout->addWidget(Button_clear);

        Button_quit = new QPushButton(layoutWidget1);
        Button_quit->setObjectName(QStringLiteral("Button_quit"));
        Button_quit->setEnabled(true);
        Button_quit->setMinimumSize(QSize(95, 60));
        Button_quit->setStyleSheet(QStringLiteral("background-image: url(:/image/button_quit);"));

        horizontalLayout->addWidget(Button_quit);

        MainWindow->setCentralWidget(centralWidget);
        layoutWidget->raise();
        graphicsView->raise();
        layoutWidget->raise();
        progressBar->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        Button0->setText(QString());
        Button1->setText(QString());
        Button2->setText(QString());
        Button3->setText(QString());
        Button4->setText(QString());
        Button_clear->setText(QString());
        Button_quit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
