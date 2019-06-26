/********************************************************************************
** Form generated from reading UI file 'miniled_vs.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINILED_VS_H
#define UI_MINILED_VS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_miniLED_vsClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *miniLED_vsClass)
    {
        if (miniLED_vsClass->objectName().isEmpty())
            miniLED_vsClass->setObjectName(QStringLiteral("miniLED_vsClass"));
        miniLED_vsClass->resize(600, 400);
        menuBar = new QMenuBar(miniLED_vsClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        miniLED_vsClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(miniLED_vsClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        miniLED_vsClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(miniLED_vsClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        miniLED_vsClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(miniLED_vsClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        miniLED_vsClass->setStatusBar(statusBar);

        retranslateUi(miniLED_vsClass);

        QMetaObject::connectSlotsByName(miniLED_vsClass);
    } // setupUi

    void retranslateUi(QMainWindow *miniLED_vsClass)
    {
        miniLED_vsClass->setWindowTitle(QApplication::translate("miniLED_vsClass", "miniLED_vs", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class miniLED_vsClass: public Ui_miniLED_vsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINILED_VS_H
