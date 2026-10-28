/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label_trem1;
    QLabel *label_trem2;
    QLabel *label_trem3;
    QLabel *label_trilho1;
    QLabel *label_trilho2;
    QLabel *label_trilho3;
    QLabel *label_trilho4;
    QLabel *label_trilho5;
    QLabel *label_trilho6;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(600, 600);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        label_trem1 = new QLabel(centralWidget);
        label_trem1->setObjectName("label_trem1");
        label_trem1->setGeometry(QRect(125, 50, 20, 20));
        label_trem1->setStyleSheet(QString::fromUtf8("QLabel { background: yellow }"));
        label_trem2 = new QLabel(centralWidget);
        label_trem2->setObjectName("label_trem2");
        label_trem2->setGeometry(QRect(125, 150, 20, 20));
        label_trem2->setStyleSheet(QString::fromUtf8("QLabel { background: green }"));
        label_trem3 = new QLabel(centralWidget);
        label_trem3->setObjectName("label_trem3");
        label_trem3->setGeometry(QRect(275, 150, 20, 20));
        label_trem3->setStyleSheet(QString::fromUtf8("QLabel { background: blue }"));
        label_trilho1 = new QLabel(centralWidget);
        label_trilho1->setObjectName("label_trilho1");
        label_trilho1->setGeometry(QRect(125, 50, 300, 20));
        label_trilho1->setStyleSheet(QString::fromUtf8("QLabel { background: black }"));
        label_trilho2 = new QLabel(centralWidget);
        label_trilho2->setObjectName("label_trilho2");
        label_trilho2->setGeometry(QRect(125, 50, 20, 100));
        label_trilho2->setStyleSheet(QString::fromUtf8("QLabel { background: black }"));
        label_trilho3 = new QLabel(centralWidget);
        label_trilho3->setObjectName("label_trilho3");
        label_trilho3->setGeometry(QRect(125, 150, 150, 20));
        label_trilho3->setStyleSheet(QString::fromUtf8("QLabel { background: red }"));
        label_trilho4 = new QLabel(centralWidget);
        label_trilho4->setObjectName("label_trilho4");
        label_trilho4->setGeometry(QRect(295, 150, 150, 20));
        label_trilho4->setStyleSheet(QString::fromUtf8("QLabel { background: red }"));
        label_trilho5 = new QLabel(centralWidget);
        label_trilho5->setObjectName("label_trilho5");
        label_trilho5->setGeometry(QRect(425, 50, 20, 100));
        label_trilho5->setStyleSheet(QString::fromUtf8("QLabel { background: black }"));
        label_trilho6 = new QLabel(centralWidget);
        label_trilho6->setObjectName("label_trilho6");
        label_trilho6->setGeometry(QRect(125, 150, 20, 100));
        label_trilho6->setStyleSheet(QString::fromUtf8("QLabel { background: black }"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(230, 180, 99, 27));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(350, 180, 98, 27));
        MainWindow->setCentralWidget(centralWidget);
        label_trem1->raise();
        label_trem2->raise();
        label_trem3->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 641, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Projeto dos Trens", nullptr));
        label_trem1->setText(QCoreApplication::translate("MainWindow", "T1", nullptr));
        label_trem2->setText(QCoreApplication::translate("MainWindow", "T2", nullptr));
        label_trem3->setText(QCoreApplication::translate("MainWindow", "T3", nullptr));
        label_trilho1->setText(QString());
        label_trilho2->setText(QString());
        label_trilho3->setText(QString());
        label_trilho4->setText(QString());
        label_trilho5->setText(QString());
        label_trilho6->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "Ligar", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Parar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
