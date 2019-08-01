/********************************************************************************
** Form generated from reading UI file 'miniled_server.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINILED_SERVER_H
#define UI_MINILED_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_miniLED_ServerClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *miniLED_ServerClass)
    {
        if (miniLED_ServerClass->objectName().isEmpty())
            miniLED_ServerClass->setObjectName(QStringLiteral("miniLED_ServerClass"));
        miniLED_ServerClass->setWindowModality(Qt::NonModal);
        miniLED_ServerClass->resize(800, 900);
        miniLED_ServerClass->setMinimumSize(QSize(800, 900));
        centralWidget = new QWidget(miniLED_ServerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QStringLiteral("background-color: rgb(88, 255, 102);"));

        horizontalLayout->addWidget(widget);

        miniLED_ServerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(miniLED_ServerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 23));
        miniLED_ServerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(miniLED_ServerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        miniLED_ServerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(miniLED_ServerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        miniLED_ServerClass->setStatusBar(statusBar);

        retranslateUi(miniLED_ServerClass);

        QMetaObject::connectSlotsByName(miniLED_ServerClass);
    } // setupUi

    void retranslateUi(QMainWindow *miniLED_ServerClass)
    {
        miniLED_ServerClass->setWindowTitle(QApplication::translate("miniLED_ServerClass", "miniLED_Server", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class miniLED_ServerClass: public Ui_miniLED_ServerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINILED_SERVER_H
