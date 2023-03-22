/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QPushButton *calibrationButton;
    QVBoxLayout *consoleLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_5;
    QLabel *calibrationLamp;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QSpinBox *positionBox;
    QPushButton *resetButton;
    QPushButton *offButton;
    QPushButton *onButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QLabel *errorLamp;
    QPushButton *stopButton;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_10;
    QLineEdit *portEdit;
    QLabel *label_27;
    QSpinBox *serverEdit;
    QPushButton *connectButton;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QLabel *positionNowLabel;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_8;
    QLabel *statusLamp;
    QPushButton *backButton;
    QPushButton *goButton;
    QPushButton *jogPlusButton;
    QPushButton *jogMinusButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(768, 388);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        calibrationButton = new QPushButton(centralwidget);
        calibrationButton->setObjectName(QString::fromUtf8("calibrationButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(calibrationButton->sizePolicy().hasHeightForWidth());
        calibrationButton->setSizePolicy(sizePolicy);
        calibrationButton->setMinimumSize(QSize(0, 100));

        gridLayout_2->addWidget(calibrationButton, 1, 2, 1, 1);

        consoleLayout = new QVBoxLayout();
        consoleLayout->setObjectName(QString::fromUtf8("consoleLayout"));

        gridLayout_2->addLayout(consoleLayout, 7, 0, 1, 4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout->addWidget(label_5);

        calibrationLamp = new QLabel(centralwidget);
        calibrationLamp->setObjectName(QString::fromUtf8("calibrationLamp"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(100);
        sizePolicy1.setVerticalStretch(100);
        sizePolicy1.setHeightForWidth(calibrationLamp->sizePolicy().hasHeightForWidth());
        calibrationLamp->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(calibrationLamp);


        gridLayout_2->addLayout(horizontalLayout, 4, 2, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(0, 0));

        horizontalLayout_5->addWidget(label);

        positionBox = new QSpinBox(centralwidget);
        positionBox->setObjectName(QString::fromUtf8("positionBox"));
        sizePolicy.setHeightForWidth(positionBox->sizePolicy().hasHeightForWidth());
        positionBox->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(positionBox);


        gridLayout_2->addLayout(horizontalLayout_5, 2, 1, 1, 1);

        resetButton = new QPushButton(centralwidget);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        sizePolicy.setHeightForWidth(resetButton->sizePolicy().hasHeightForWidth());
        resetButton->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(resetButton, 5, 3, 1, 1);

        offButton = new QPushButton(centralwidget);
        offButton->setObjectName(QString::fromUtf8("offButton"));
        sizePolicy.setHeightForWidth(offButton->sizePolicy().hasHeightForWidth());
        offButton->setSizePolicy(sizePolicy);
        offButton->setMinimumSize(QSize(0, 100));

        gridLayout_2->addWidget(offButton, 2, 3, 1, 1);

        onButton = new QPushButton(centralwidget);
        onButton->setObjectName(QString::fromUtf8("onButton"));
        sizePolicy.setHeightForWidth(onButton->sizePolicy().hasHeightForWidth());
        onButton->setSizePolicy(sizePolicy);
        onButton->setMinimumSize(QSize(0, 100));

        gridLayout_2->addWidget(onButton, 1, 3, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_2->addWidget(label_6);

        errorLamp = new QLabel(centralwidget);
        errorLamp->setObjectName(QString::fromUtf8("errorLamp"));
        sizePolicy1.setHeightForWidth(errorLamp->sizePolicy().hasHeightForWidth());
        errorLamp->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(errorLamp);


        gridLayout_2->addLayout(horizontalLayout_2, 5, 2, 1, 1);

        stopButton = new QPushButton(centralwidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        sizePolicy.setHeightForWidth(stopButton->sizePolicy().hasHeightForWidth());
        stopButton->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(stopButton, 4, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(label_10);

        portEdit = new QLineEdit(centralwidget);
        portEdit->setObjectName(QString::fromUtf8("portEdit"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(portEdit->sizePolicy().hasHeightForWidth());
        portEdit->setSizePolicy(sizePolicy3);

        horizontalLayout_4->addWidget(portEdit);

        label_27 = new QLabel(centralwidget);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        sizePolicy2.setHeightForWidth(label_27->sizePolicy().hasHeightForWidth());
        label_27->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(label_27);

        serverEdit = new QSpinBox(centralwidget);
        serverEdit->setObjectName(QString::fromUtf8("serverEdit"));
        sizePolicy2.setHeightForWidth(serverEdit->sizePolicy().hasHeightForWidth());
        serverEdit->setSizePolicy(sizePolicy2);
        serverEdit->setMinimum(1);
        serverEdit->setMaximum(247);

        horizontalLayout_4->addWidget(serverEdit);

        connectButton = new QPushButton(centralwidget);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        sizePolicy2.setHeightForWidth(connectButton->sizePolicy().hasHeightForWidth());
        connectButton->setSizePolicy(sizePolicy2);
        connectButton->setCheckable(false);
        connectButton->setAutoDefault(false);

        horizontalLayout_4->addWidget(connectButton);


        gridLayout_2->addLayout(horizontalLayout_4, 0, 0, 1, 4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(0, 0));

        horizontalLayout_6->addWidget(label_2);

        positionNowLabel = new QLabel(centralwidget);
        positionNowLabel->setObjectName(QString::fromUtf8("positionNowLabel"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(positionNowLabel->sizePolicy().hasHeightForWidth());
        positionNowLabel->setSizePolicy(sizePolicy4);

        horizontalLayout_6->addWidget(positionNowLabel);


        gridLayout_2->addLayout(horizontalLayout_6, 2, 2, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_3->addWidget(label_8);

        statusLamp = new QLabel(centralwidget);
        statusLamp->setObjectName(QString::fromUtf8("statusLamp"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(statusLamp->sizePolicy().hasHeightForWidth());
        statusLamp->setSizePolicy(sizePolicy5);

        horizontalLayout_3->addWidget(statusLamp);


        gridLayout_2->addLayout(horizontalLayout_3, 4, 3, 1, 1);

        backButton = new QPushButton(centralwidget);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        sizePolicy.setHeightForWidth(backButton->sizePolicy().hasHeightForWidth());
        backButton->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(backButton, 5, 1, 1, 1);

        goButton = new QPushButton(centralwidget);
        goButton->setObjectName(QString::fromUtf8("goButton"));
        sizePolicy.setHeightForWidth(goButton->sizePolicy().hasHeightForWidth());
        goButton->setSizePolicy(sizePolicy);
        goButton->setMinimumSize(QSize(0, 100));

        gridLayout_2->addWidget(goButton, 1, 1, 1, 1);

        jogPlusButton = new QPushButton(centralwidget);
        jogPlusButton->setObjectName(QString::fromUtf8("jogPlusButton"));
        sizePolicy.setHeightForWidth(jogPlusButton->sizePolicy().hasHeightForWidth());
        jogPlusButton->setSizePolicy(sizePolicy);
        jogPlusButton->setMinimumSize(QSize(0, 100));

        gridLayout_2->addWidget(jogPlusButton, 1, 0, 1, 1);

        jogMinusButton = new QPushButton(centralwidget);
        jogMinusButton->setObjectName(QString::fromUtf8("jogMinusButton"));
        sizePolicy.setHeightForWidth(jogMinusButton->sizePolicy().hasHeightForWidth());
        jogMinusButton->setSizePolicy(sizePolicy);
        jogMinusButton->setMinimumSize(QSize(0, 100));

        gridLayout_2->addWidget(jogMinusButton, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 768, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        connectButton->setDefault(true);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        calibrationButton->setText(QCoreApplication::translate("MainWindow", "\320\232\320\220\320\233\320\230\320\221\320\240\320\236\320\222\320\232\320\220", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\232\320\260\320\273\320\270\320\261\321\200\320\276\320\262\320\272\320\260", nullptr));
        calibrationLamp->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\267\320\270\321\206\320\270\321\217:", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\221\320\240\320\236\320\241", nullptr));
        offButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\253\320\232\320\233", nullptr));
        onButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\232\320\233", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\236\321\210\320\270\320\261\320\272\320\260", nullptr));
        errorLamp->setText(QString());
        stopButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\242\320\236\320\237", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Port:", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "Server Address:", nullptr));
        connectButton->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\272\321\203\321\211\320\260\321\217 \320\277\320\276\320\267\320\270\321\206\320\270\321\217:", nullptr));
        positionNowLabel->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\321\203\321\201", nullptr));
        statusLamp->setText(QString());
        backButton->setText(QCoreApplication::translate("MainWindow", "\320\235\320\220\320\227\320\220\320\224", nullptr));
        goButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\225\320\240\320\225\320\234\320\225\320\241\320\242\320\230\320\242\320\254", nullptr));
        jogPlusButton->setText(QCoreApplication::translate("MainWindow", "\320\242\320\243\320\224\320\220", nullptr));
        jogMinusButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\256\320\224\320\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
