/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[512];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 30), // "on_checkBox_OutlineGap_clicked"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 7), // "checked"
QT_MOC_LITERAL(4, 51, 34), // "on_pushButton_ParameterSet_cl..."
QT_MOC_LITERAL(5, 86, 39), // "on_pushButton_CameraCalibrati..."
QT_MOC_LITERAL(6, 126, 33), // "on_pushButton_PickPicture_cli..."
QT_MOC_LITERAL(7, 160, 39), // "on_pushButton_CalibrationResu..."
QT_MOC_LITERAL(8, 200, 48), // "on_comboBox_SelectConnectWay_..."
QT_MOC_LITERAL(9, 249, 5), // "index"
QT_MOC_LITERAL(10, 255, 44), // "on_horizontalSlider_ExposureT..."
QT_MOC_LITERAL(11, 300, 8), // "position"
QT_MOC_LITERAL(12, 309, 36), // "on_lineEdit_Aperture_editingF..."
QT_MOC_LITERAL(13, 346, 14), // "loadStyleSheet"
QT_MOC_LITERAL(14, 361, 14), // "styleSheetFile"
QT_MOC_LITERAL(15, 376, 30), // "on_dial_brightness_sliderMoved"
QT_MOC_LITERAL(16, 407, 35), // "on_pushButton_ConnectCamera_c..."
QT_MOC_LITERAL(17, 443, 38), // "on_lineEdit_ExposureTime_retu..."
QT_MOC_LITERAL(18, 482, 29) // "on_pushButton_Confirm_clicked"

    },
    "MainWindow\0on_checkBox_OutlineGap_clicked\0"
    "\0checked\0on_pushButton_ParameterSet_clicked\0"
    "on_pushButton_CameraCalibration_clicked\0"
    "on_pushButton_PickPicture_clicked\0"
    "on_pushButton_CalibrationResult_clicked\0"
    "on_comboBox_SelectConnectWay_currentIndexChanged\0"
    "index\0on_horizontalSlider_ExposureTime_sliderMoved\0"
    "position\0on_lineEdit_Aperture_editingFinished\0"
    "loadStyleSheet\0styleSheetFile\0"
    "on_dial_brightness_sliderMoved\0"
    "on_pushButton_ConnectCamera_clicked\0"
    "on_lineEdit_ExposureTime_returnPressed\0"
    "on_pushButton_Confirm_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x08 /* Private */,
       4,    0,   82,    2, 0x08 /* Private */,
       5,    0,   83,    2, 0x08 /* Private */,
       6,    0,   84,    2, 0x08 /* Private */,
       7,    0,   85,    2, 0x08 /* Private */,
       8,    1,   86,    2, 0x08 /* Private */,
      10,    1,   89,    2, 0x08 /* Private */,
      12,    0,   92,    2, 0x08 /* Private */,
      13,    1,   93,    2, 0x08 /* Private */,
      15,    1,   96,    2, 0x08 /* Private */,
      16,    0,   99,    2, 0x08 /* Private */,
      17,    0,  100,    2, 0x08 /* Private */,
      18,    0,  101,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_checkBox_OutlineGap_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_pushButton_ParameterSet_clicked(); break;
        case 2: _t->on_pushButton_CameraCalibration_clicked(); break;
        case 3: _t->on_pushButton_PickPicture_clicked(); break;
        case 4: _t->on_pushButton_CalibrationResult_clicked(); break;
        case 5: _t->on_comboBox_SelectConnectWay_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_horizontalSlider_ExposureTime_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_lineEdit_Aperture_editingFinished(); break;
        case 8: _t->loadStyleSheet((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->on_dial_brightness_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_pushButton_ConnectCamera_clicked(); break;
        case 11: _t->on_lineEdit_ExposureTime_returnPressed(); break;
        case 12: _t->on_pushButton_Confirm_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
