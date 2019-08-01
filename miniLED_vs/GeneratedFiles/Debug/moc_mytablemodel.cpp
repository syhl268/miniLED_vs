/****************************************************************************
** Meta object code from reading C++ file 'mytablemodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mytablemodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mytablemodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyTableModel_t {
    QByteArrayData data[10];
    char stringdata0[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyTableModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyTableModel_t qt_meta_stringdata_MyTableModel = {
    {
QT_MOC_LITERAL(0, 0, 12), // "MyTableModel"
QT_MOC_LITERAL(1, 13, 8), // "rowCount"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 6), // "parent"
QT_MOC_LITERAL(4, 30, 11), // "columnCount"
QT_MOC_LITERAL(5, 42, 4), // "data"
QT_MOC_LITERAL(6, 47, 5), // "index"
QT_MOC_LITERAL(7, 53, 4), // "role"
QT_MOC_LITERAL(8, 58, 7), // "setData"
QT_MOC_LITERAL(9, 66, 5) // "value"

    },
    "MyTableModel\0rowCount\0\0parent\0columnCount\0"
    "data\0index\0role\0setData\0value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyTableModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x02 /* Public */,
       1,    0,   57,    2, 0x22 /* Public | MethodCloned */,
       4,    1,   58,    2, 0x02 /* Public */,
       4,    0,   61,    2, 0x22 /* Public | MethodCloned */,
       5,    2,   62,    2, 0x02 /* Public */,
       5,    1,   67,    2, 0x22 /* Public | MethodCloned */,
       8,    3,   70,    2, 0x02 /* Public */,
       8,    2,   77,    2, 0x22 /* Public | MethodCloned */,

 // methods: parameters
    QMetaType::Int, QMetaType::QModelIndex,    3,
    QMetaType::Int,
    QMetaType::Int, QMetaType::QModelIndex,    3,
    QMetaType::Int,
    QMetaType::QVariant, QMetaType::QModelIndex, QMetaType::Int,    6,    7,
    QMetaType::QVariant, QMetaType::QModelIndex,    6,
    QMetaType::Bool, QMetaType::QModelIndex, QMetaType::QVariant, QMetaType::Int,    6,    9,    7,
    QMetaType::Bool, QMetaType::QModelIndex, QMetaType::QVariant,    6,    9,

       0        // eod
};

void MyTableModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyTableModel *_t = static_cast<MyTableModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->rowCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: { int _r = _t->rowCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 2: { int _r = _t->columnCount((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->columnCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: { bool _r = _t->setData((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: { bool _r = _t->setData((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject MyTableModel::staticMetaObject = {
    { &QAbstractTableModel::staticMetaObject, qt_meta_stringdata_MyTableModel.data,
      qt_meta_data_MyTableModel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MyTableModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyTableModel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MyTableModel.stringdata0))
        return static_cast<void*>(const_cast< MyTableModel*>(this));
    return QAbstractTableModel::qt_metacast(_clname);
}

int MyTableModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
