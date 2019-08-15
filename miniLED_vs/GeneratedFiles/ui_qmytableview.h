/********************************************************************************
** Form generated from reading UI file 'qmytableview.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QMYTABLEVIEW_H
#define UI_QMYTABLEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_QMyTableView
{
public:

    void setupUi(QTableView *QMyTableView)
    {
        if (QMyTableView->objectName().isEmpty())
            QMyTableView->setObjectName(QStringLiteral("QMyTableView"));
        QMyTableView->resize(400, 300);
        if (QMyTableView->horizontalHeader()->objectName().isEmpty())
        if (QMyTableView->verticalHeader()->objectName().isEmpty())

        retranslateUi(QMyTableView);

        QMetaObject::connectSlotsByName(QMyTableView);
    } // setupUi

    void retranslateUi(QTableView *QMyTableView)
    {
        QMyTableView->setWindowTitle(QApplication::translate("QMyTableView", "QMyTableView", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QMyTableView: public Ui_QMyTableView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QMYTABLEVIEW_H
