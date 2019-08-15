/********************************************************************************
** Form generated from reading UI file 'qscaletableview.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QSCALETABLEVIEW_H
#define UI_QSCALETABLEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_QScaleTableView
{
public:

    void setupUi(QTableView *QScaleTableView)
    {
        if (QScaleTableView->objectName().isEmpty())
            QScaleTableView->setObjectName(QStringLiteral("QScaleTableView"));
        QScaleTableView->resize(400, 300);
        if (QScaleTableView->horizontalHeader()->objectName().isEmpty())
        if (QScaleTableView->verticalHeader()->objectName().isEmpty())

        retranslateUi(QScaleTableView);

        QMetaObject::connectSlotsByName(QScaleTableView);
    } // setupUi

    void retranslateUi(QTableView *QScaleTableView)
    {
        QScaleTableView->setWindowTitle(QApplication::translate("QScaleTableView", "QScaleTableView", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QScaleTableView: public Ui_QScaleTableView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QSCALETABLEVIEW_H
