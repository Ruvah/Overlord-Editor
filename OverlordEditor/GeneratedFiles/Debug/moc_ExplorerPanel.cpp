/****************************************************************************
** Meta object code from reading C++ file 'ExplorerPanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../ExplorerPanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ExplorerPanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ExplorerPanel_t {
    QByteArrayData data[11];
    char stringdata0[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ExplorerPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ExplorerPanel_t qt_meta_stringdata_ExplorerPanel = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ExplorerPanel"
QT_MOC_LITERAL(1, 14, 11), // "OnDirSelect"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 14), // "OnFileDblClick"
QT_MOC_LITERAL(4, 42, 11), // "OnFileClick"
QT_MOC_LITERAL(5, 54, 11), // "FileRenamed"
QT_MOC_LITERAL(6, 66, 4), // "path"
QT_MOC_LITERAL(7, 71, 7), // "oldName"
QT_MOC_LITERAL(8, 79, 7), // "newName"
QT_MOC_LITERAL(9, 87, 11), // "NewPhysxMat"
QT_MOC_LITERAL(10, 99, 8) // "NewScene"

    },
    "ExplorerPanel\0OnDirSelect\0\0OnFileDblClick\0"
    "OnFileClick\0FileRenamed\0path\0oldName\0"
    "newName\0NewPhysxMat\0NewScene"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ExplorerPanel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x0a /* Public */,
       5,    3,   47,    2, 0x0a /* Public */,
       9,    0,   54,    2, 0x0a /* Public */,
      10,    0,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    6,    7,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ExplorerPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ExplorerPanel *_t = static_cast<ExplorerPanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnDirSelect(); break;
        case 1: _t->OnFileDblClick(); break;
        case 2: _t->OnFileClick(); break;
        case 3: _t->FileRenamed((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 4: _t->NewPhysxMat(); break;
        case 5: _t->NewScene(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ExplorerPanel::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ExplorerPanel.data,
      qt_meta_data_ExplorerPanel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ExplorerPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExplorerPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ExplorerPanel.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Subject"))
        return static_cast< Subject*>(this);
    return QWidget::qt_metacast(_clname);
}

int ExplorerPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
