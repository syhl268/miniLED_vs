/********************************************************************************
** Form generated from reading UI file 'direselector.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIRESELECTOR_H
#define UI_DIRESELECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_direSelector
{
public:

    void setupUi(QWidget *direSelector)
    {
        if (direSelector->objectName().isEmpty())
            direSelector->setObjectName(QStringLiteral("direSelector"));
        direSelector->resize(400, 300);

        retranslateUi(direSelector);

        QMetaObject::connectSlotsByName(direSelector);
    } // setupUi

    void retranslateUi(QWidget *direSelector)
    {
        direSelector->setWindowTitle(QApplication::translate("direSelector", "direSelector", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class direSelector: public Ui_direSelector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIRESELECTOR_H
