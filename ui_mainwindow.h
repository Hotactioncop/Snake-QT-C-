/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "space.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QPushButton *buttonStart;
    QPushButton *buttonPause;
    QPushButton *buttonStop;
    QPushButton *buttonExit;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QLCDNumber *lcdNumber;
    QSpacerItem *verticalSpacer_2;
    Space *LayoutSpace;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(546, 371);
        QIcon icon;
        icon.addFile(QString::fromUtf8("Images/wpsofficeetmain_94386.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        buttonStart = new QPushButton(centralWidget);
        buttonStart->setObjectName(QString::fromUtf8("buttonStart"));
        buttonStart->setMinimumSize(QSize(20, 0));
        buttonStart->setMaximumSize(QSize(80, 30));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("Images/ios-8-Game-Center-icon_43822.ico"), QSize(), QIcon::Normal, QIcon::Off);
        buttonStart->setIcon(icon1);

        verticalLayout_2->addWidget(buttonStart);

        buttonPause = new QPushButton(centralWidget);
        buttonPause->setObjectName(QString::fromUtf8("buttonPause"));
        buttonPause->setMaximumSize(QSize(80, 30));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("Images/PauseDisabled_26933.ico"), QSize(), QIcon::Normal, QIcon::Off);
        buttonPause->setIcon(icon2);

        verticalLayout_2->addWidget(buttonPause);

        buttonStop = new QPushButton(centralWidget);
        buttonStop->setObjectName(QString::fromUtf8("buttonStop"));
        buttonStop->setMaximumSize(QSize(80, 30));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("Images/Stop_37106.ico"), QSize(), QIcon::Normal, QIcon::Off);
        buttonStop->setIcon(icon3);

        verticalLayout_2->addWidget(buttonStop);

        buttonExit = new QPushButton(centralWidget);
        buttonExit->setObjectName(QString::fromUtf8("buttonExit"));
        buttonExit->setMaximumSize(QSize(80, 30));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("Images/exit_closethesession_close_6317.ico"), QSize(), QIcon::Normal, QIcon::Off);
        buttonExit->setIcon(icon4);

        verticalLayout_2->addWidget(buttonExit);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(80, 0));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setMaximumSize(QSize(80, 30));
        lcdNumber->setFrameShape(QFrame::Box);
        lcdNumber->setFrameShadow(QFrame::Raised);
        lcdNumber->setDigitCount(8);
        lcdNumber->setSegmentStyle(QLCDNumber::Flat);

        verticalLayout_2->addWidget(lcdNumber);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);

        LayoutSpace = new Space(centralWidget);
        LayoutSpace->setObjectName(QString::fromUtf8("LayoutSpace"));
        LayoutSpace->setEnabled(true);
        LayoutSpace->setMinimumSize(QSize(440, 300));

        gridLayout->addWidget(LayoutSpace, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 546, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(buttonExit, SIGNAL(clicked()), MainWindow, SLOT(close()));
        QObject::connect(buttonStart, SIGNAL(clicked()), LayoutSpace, SLOT(startGame()));
        QObject::connect(buttonPause, SIGNAL(clicked()), LayoutSpace, SLOT(pauseGame()));
        QObject::connect(LayoutSpace, SIGNAL(changePause()), MainWindow, SLOT(changePauseButton()));
        QObject::connect(LayoutSpace, SIGNAL(setScore(int)), lcdNumber, SLOT(display(int)));
        QObject::connect(buttonStop, SIGNAL(clicked()), LayoutSpace, SLOT(stopGame()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Snake", nullptr));
        buttonStart->setText(QApplication::translate("MainWindow", "Start", nullptr));
        buttonPause->setText(QApplication::translate("MainWindow", "Pause", nullptr));
        buttonStop->setText(QApplication::translate("MainWindow", "Stop", nullptr));
        buttonExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        label->setText(QApplication::translate("MainWindow", "Score", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
