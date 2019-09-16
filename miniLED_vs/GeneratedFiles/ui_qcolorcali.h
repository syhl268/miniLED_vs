/********************************************************************************
** Form generated from reading UI file 'qcolorcali.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCOLORCALI_H
#define UI_QCOLORCALI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QColorCali
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *groupBox_13;
    QWidget *widget_10;
    QHBoxLayout *horizontalLayout_8;
    QRadioButton *radioButton_testRed;
    QRadioButton *radioButton_testGreen;
    QRadioButton *radioButton_testBlue;
    QRadioButton *radioButton_testWhite;
    QSpinBox *spinBox_GL;
    QTableWidget *tableWidget;
    QWidget *tab_2;
    QFrame *frame_2;
    QGridLayout *gridLayout;
    QRadioButton *radioButton_sRGB;
    QRadioButton *radioButton_AdobeRGB;
    QRadioButton *radioButton_DCI_P3;
    QRadioButton *radioButton_Rec_601;
    QRadioButton *radioButton_Rec_709;
    QRadioButton *radioButton_Rec_2020;
    QRadioButton *radioButton_PAL;
    QRadioButton *radioButton_NTSC;
    QRadioButton *radioButton_CustomStd;
    QTableWidget *tableWidget_ColorCoord;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *label_ColormapShow;

    void setupUi(QDialog *QColorCali)
    {
        if (QColorCali->objectName().isEmpty())
            QColorCali->setObjectName(QStringLiteral("QColorCali"));
        QColorCali->resize(962, 619);
        tabWidget = new QTabWidget(QColorCali);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(570, 10, 381, 591));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        groupBox_13 = new QGroupBox(tab);
        groupBox_13->setObjectName(QStringLiteral("groupBox_13"));
        groupBox_13->setGeometry(QRect(20, 20, 341, 111));
        widget_10 = new QWidget(groupBox_13);
        widget_10->setObjectName(QStringLiteral("widget_10"));
        widget_10->setGeometry(QRect(0, 10, 331, 81));
        horizontalLayout_8 = new QHBoxLayout(widget_10);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        radioButton_testRed = new QRadioButton(widget_10);
        radioButton_testRed->setObjectName(QStringLiteral("radioButton_testRed"));
        radioButton_testRed->setChecked(true);

        horizontalLayout_8->addWidget(radioButton_testRed);

        radioButton_testGreen = new QRadioButton(widget_10);
        radioButton_testGreen->setObjectName(QStringLiteral("radioButton_testGreen"));

        horizontalLayout_8->addWidget(radioButton_testGreen);

        radioButton_testBlue = new QRadioButton(widget_10);
        radioButton_testBlue->setObjectName(QStringLiteral("radioButton_testBlue"));

        horizontalLayout_8->addWidget(radioButton_testBlue);

        radioButton_testWhite = new QRadioButton(widget_10);
        radioButton_testWhite->setObjectName(QStringLiteral("radioButton_testWhite"));

        horizontalLayout_8->addWidget(radioButton_testWhite);

        spinBox_GL = new QSpinBox(widget_10);
        spinBox_GL->setObjectName(QStringLiteral("spinBox_GL"));
        spinBox_GL->setMaximum(255);
        spinBox_GL->setValue(255);

        horizontalLayout_8->addWidget(spinBox_GL);

        tableWidget = new QTableWidget(tab);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableWidget->rowCount() < 4)
            tableWidget->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsTristate);
        tableWidget->setItem(0, 0, __qtablewidgetitem7);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(20, 140, 341, 171));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        frame_2 = new QFrame(tab_2);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(10, 10, 361, 111));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        radioButton_sRGB = new QRadioButton(frame_2);
        radioButton_sRGB->setObjectName(QStringLiteral("radioButton_sRGB"));
        radioButton_sRGB->setMinimumSize(QSize(120, 0));
        radioButton_sRGB->setChecked(true);

        gridLayout->addWidget(radioButton_sRGB, 0, 0, 1, 1);

        radioButton_AdobeRGB = new QRadioButton(frame_2);
        radioButton_AdobeRGB->setObjectName(QStringLiteral("radioButton_AdobeRGB"));
        radioButton_AdobeRGB->setMinimumSize(QSize(120, 0));

        gridLayout->addWidget(radioButton_AdobeRGB, 0, 1, 1, 1);

        radioButton_DCI_P3 = new QRadioButton(frame_2);
        radioButton_DCI_P3->setObjectName(QStringLiteral("radioButton_DCI_P3"));
        radioButton_DCI_P3->setMinimumSize(QSize(120, 0));

        gridLayout->addWidget(radioButton_DCI_P3, 0, 2, 1, 1);

        radioButton_Rec_601 = new QRadioButton(frame_2);
        radioButton_Rec_601->setObjectName(QStringLiteral("radioButton_Rec_601"));
        radioButton_Rec_601->setMinimumSize(QSize(120, 0));

        gridLayout->addWidget(radioButton_Rec_601, 1, 0, 1, 1);

        radioButton_Rec_709 = new QRadioButton(frame_2);
        radioButton_Rec_709->setObjectName(QStringLiteral("radioButton_Rec_709"));
        radioButton_Rec_709->setMinimumSize(QSize(120, 0));

        gridLayout->addWidget(radioButton_Rec_709, 1, 1, 1, 1);

        radioButton_Rec_2020 = new QRadioButton(frame_2);
        radioButton_Rec_2020->setObjectName(QStringLiteral("radioButton_Rec_2020"));
        radioButton_Rec_2020->setMinimumSize(QSize(120, 0));

        gridLayout->addWidget(radioButton_Rec_2020, 1, 2, 1, 1);

        radioButton_PAL = new QRadioButton(frame_2);
        radioButton_PAL->setObjectName(QStringLiteral("radioButton_PAL"));
        radioButton_PAL->setMinimumSize(QSize(120, 0));

        gridLayout->addWidget(radioButton_PAL, 2, 0, 1, 1);

        radioButton_NTSC = new QRadioButton(frame_2);
        radioButton_NTSC->setObjectName(QStringLiteral("radioButton_NTSC"));
        radioButton_NTSC->setMinimumSize(QSize(120, 0));

        gridLayout->addWidget(radioButton_NTSC, 2, 1, 1, 1);

        radioButton_CustomStd = new QRadioButton(frame_2);
        radioButton_CustomStd->setObjectName(QStringLiteral("radioButton_CustomStd"));
        radioButton_CustomStd->setMinimumSize(QSize(120, 0));

        gridLayout->addWidget(radioButton_CustomStd, 2, 2, 1, 1);

        tableWidget_ColorCoord = new QTableWidget(tab_2);
        if (tableWidget_ColorCoord->columnCount() < 3)
            tableWidget_ColorCoord->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_ColorCoord->setHorizontalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_ColorCoord->setHorizontalHeaderItem(1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_ColorCoord->setHorizontalHeaderItem(2, __qtablewidgetitem10);
        if (tableWidget_ColorCoord->rowCount() < 4)
            tableWidget_ColorCoord->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_ColorCoord->setVerticalHeaderItem(0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_ColorCoord->setVerticalHeaderItem(1, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget_ColorCoord->setVerticalHeaderItem(2, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget_ColorCoord->setVerticalHeaderItem(3, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        __qtablewidgetitem15->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsTristate);
        tableWidget_ColorCoord->setItem(0, 0, __qtablewidgetitem15);
        tableWidget_ColorCoord->setObjectName(QStringLiteral("tableWidget_ColorCoord"));
        tableWidget_ColorCoord->setGeometry(QRect(10, 140, 341, 161));
        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 320, 361, 141));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(9);
        gridLayout_2->setContentsMargins(1, -1, 20, -1);
        lineEdit_4 = new QLineEdit(groupBox);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_4->sizePolicy().hasHeightForWidth());
        lineEdit_4->setSizePolicy(sizePolicy);
        lineEdit_4->setMaximumSize(QSize(16777215, 16777215));
        lineEdit_4->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lineEdit_4, 1, 0, 1, 1);

        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        sizePolicy.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy);
        lineEdit_2->setMaximumSize(QSize(16777215, 16777215));
        lineEdit_2->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lineEdit_2, 0, 1, 1, 1);

        lineEdit_7 = new QLineEdit(groupBox);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        sizePolicy.setHeightForWidth(lineEdit_7->sizePolicy().hasHeightForWidth());
        lineEdit_7->setSizePolicy(sizePolicy);
        lineEdit_7->setMaximumSize(QSize(16777215, 16777215));
        lineEdit_7->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lineEdit_7, 2, 0, 1, 1);

        lineEdit_8 = new QLineEdit(groupBox);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));
        sizePolicy.setHeightForWidth(lineEdit_8->sizePolicy().hasHeightForWidth());
        lineEdit_8->setSizePolicy(sizePolicy);
        lineEdit_8->setMaximumSize(QSize(16777215, 16777215));
        lineEdit_8->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lineEdit_8, 2, 1, 1, 1);

        lineEdit_3 = new QLineEdit(groupBox);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        sizePolicy.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy);
        lineEdit_3->setMaximumSize(QSize(16777215, 16777215));
        lineEdit_3->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lineEdit_3, 0, 2, 1, 1);

        lineEdit_5 = new QLineEdit(groupBox);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        sizePolicy.setHeightForWidth(lineEdit_5->sizePolicy().hasHeightForWidth());
        lineEdit_5->setSizePolicy(sizePolicy);
        lineEdit_5->setMaximumSize(QSize(16777215, 16777215));
        lineEdit_5->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lineEdit_5, 1, 1, 1, 1);

        lineEdit_6 = new QLineEdit(groupBox);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        sizePolicy.setHeightForWidth(lineEdit_6->sizePolicy().hasHeightForWidth());
        lineEdit_6->setSizePolicy(sizePolicy);
        lineEdit_6->setMaximumSize(QSize(16777215, 16777215));
        lineEdit_6->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lineEdit_6, 1, 2, 1, 1);

        lineEdit_9 = new QLineEdit(groupBox);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));
        sizePolicy.setHeightForWidth(lineEdit_9->sizePolicy().hasHeightForWidth());
        lineEdit_9->setSizePolicy(sizePolicy);
        lineEdit_9->setMaximumSize(QSize(16777215, 16777215));
        lineEdit_9->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lineEdit_9, 2, 2, 1, 1);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);
        lineEdit->setMaximumSize(QSize(16777215, 16777215));
        lineEdit->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lineEdit, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        frame = new QFrame(QColorCali);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(10, 10, 547, 585));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setMinimumSize(QSize(547, 585));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_ColormapShow = new QLabel(frame);
        label_ColormapShow->setObjectName(QStringLiteral("label_ColormapShow"));

        horizontalLayout->addWidget(label_ColormapShow);


        retranslateUi(QColorCali);
        QObject::connect(tableWidget_ColorCoord, SIGNAL(itemChanged(QTableWidgetItem*)), QColorCali, SLOT(on_tableWidget_ColorCoord_ItemChaged(QTableWidgetItem*)));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(QColorCali);
    } // setupUi

    void retranslateUi(QDialog *QColorCali)
    {
        QColorCali->setWindowTitle(QApplication::translate("QColorCali", "QColorCali", Q_NULLPTR));
        groupBox_13->setTitle(QApplication::translate("QColorCali", "\345\261\217\345\271\225\346\230\276\347\244\272", Q_NULLPTR));
        radioButton_testRed->setText(QApplication::translate("QColorCali", "\347\272\242", Q_NULLPTR));
        radioButton_testGreen->setText(QApplication::translate("QColorCali", "\347\273\277", Q_NULLPTR));
        radioButton_testBlue->setText(QApplication::translate("QColorCali", "\350\223\235", Q_NULLPTR));
        radioButton_testWhite->setText(QApplication::translate("QColorCali", "\347\231\275", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("QColorCali", "\344\272\256\345\272\246", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("QColorCali", "x", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("QColorCali", "y", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("QColorCali", "\347\272\242\350\211\262", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("QColorCali", "\347\273\277\350\211\262", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem5->setText(QApplication::translate("QColorCali", "\350\223\235\350\211\262", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem6->setText(QApplication::translate("QColorCali", "\347\231\275\350\211\262", Q_NULLPTR));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        tableWidget->setSortingEnabled(__sortingEnabled);

        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("QColorCali", "\345\216\237\345\247\213\345\200\274", Q_NULLPTR));
        radioButton_sRGB->setText(QApplication::translate("QColorCali", "sRGB", Q_NULLPTR));
        radioButton_AdobeRGB->setText(QApplication::translate("QColorCali", "AdobeRGB", Q_NULLPTR));
        radioButton_DCI_P3->setText(QApplication::translate("QColorCali", "DCI-P3", Q_NULLPTR));
        radioButton_Rec_601->setText(QApplication::translate("QColorCali", "Rec.601", Q_NULLPTR));
        radioButton_Rec_709->setText(QApplication::translate("QColorCali", "Rec.709", Q_NULLPTR));
        radioButton_Rec_2020->setText(QApplication::translate("QColorCali", "Rec.2020", Q_NULLPTR));
        radioButton_PAL->setText(QApplication::translate("QColorCali", "PAL", Q_NULLPTR));
        radioButton_NTSC->setText(QApplication::translate("QColorCali", "NTSC", Q_NULLPTR));
        radioButton_CustomStd->setText(QApplication::translate("QColorCali", "\350\207\252\345\256\232\344\271\211", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_ColorCoord->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QApplication::translate("QColorCali", "\344\272\256\345\272\246", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_ColorCoord->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QApplication::translate("QColorCali", "x", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_ColorCoord->horizontalHeaderItem(2);
        ___qtablewidgetitem9->setText(QApplication::translate("QColorCali", "y", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_ColorCoord->verticalHeaderItem(0);
        ___qtablewidgetitem10->setText(QApplication::translate("QColorCali", "\347\272\242\350\211\262", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_ColorCoord->verticalHeaderItem(1);
        ___qtablewidgetitem11->setText(QApplication::translate("QColorCali", "\347\273\277\350\211\262", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget_ColorCoord->verticalHeaderItem(2);
        ___qtablewidgetitem12->setText(QApplication::translate("QColorCali", "\350\223\235\350\211\262", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget_ColorCoord->verticalHeaderItem(3);
        ___qtablewidgetitem13->setText(QApplication::translate("QColorCali", "\347\231\275\350\211\262", Q_NULLPTR));

        const bool __sortingEnabled1 = tableWidget_ColorCoord->isSortingEnabled();
        tableWidget_ColorCoord->setSortingEnabled(false);
        tableWidget_ColorCoord->setSortingEnabled(__sortingEnabled1);

        groupBox->setTitle(QApplication::translate("QColorCali", "\350\260\203\346\225\264\347\237\251\351\230\265", Q_NULLPTR));
        lineEdit_4->setPlaceholderText(QApplication::translate("QColorCali", "Gr", Q_NULLPTR));
        lineEdit_2->setPlaceholderText(QApplication::translate("QColorCali", "Rg", Q_NULLPTR));
        lineEdit_7->setPlaceholderText(QApplication::translate("QColorCali", "Br", Q_NULLPTR));
        lineEdit_8->setPlaceholderText(QApplication::translate("QColorCali", "Bg", Q_NULLPTR));
        lineEdit_3->setPlaceholderText(QApplication::translate("QColorCali", "Rb", Q_NULLPTR));
        lineEdit_5->setPlaceholderText(QApplication::translate("QColorCali", "Gg", Q_NULLPTR));
        lineEdit_6->setPlaceholderText(QApplication::translate("QColorCali", "Gb", Q_NULLPTR));
        lineEdit_9->setPlaceholderText(QApplication::translate("QColorCali", "Bb", Q_NULLPTR));
        lineEdit->setPlaceholderText(QApplication::translate("QColorCali", "Rr", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("QColorCali", "\350\260\203\346\225\264", Q_NULLPTR));
        label_ColormapShow->setText(QApplication::translate("QColorCali", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QColorCali: public Ui_QColorCali {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCOLORCALI_H
