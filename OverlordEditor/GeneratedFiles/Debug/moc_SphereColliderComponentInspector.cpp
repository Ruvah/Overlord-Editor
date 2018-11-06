/****************************************************************************
** Meta object code from reading C++ file 'SphereColliderComponentInspector.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../SphereColliderComponentInspector.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SphereColliderComponentInspector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SphereColliderComponentInspector_t {
    QByteArrayData data[6];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SphereColliderComponentInspector_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SphereColliderComponentInspector_t qt_meta_stringdata_SphereColliderComponentInspector = {
    {
QT_MOC_LITERAL(0, 0, 32), // "SphereColliderComponentInspector"
QT_MOC_LITERAL(1, 33, 13), // "RadiusChanged"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 15), // "RotationChanged"
QT_MOC_LITERAL(4, 64, 16), // "IsTriggerChanged"
QT_MOC_LITERAL(5, 81, 15) // "MaterialChanged"

    },
    "SphereColliderComponentInspector\0"
    "RadiusChanged\0\0RotationChanged\0"
    "IsTriggerChanged\0MaterialChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SphereColliderComponentInspector[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       4,    0,   36,    2, 0x0a /* Public */,
       5,    0,   37,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SphereColliderComponentInspector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SphereColliderComponentInspector *_t = static_cast<SphereColliderComponentInspector *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->RadiusChanged(); break;
        case 1: _t->RotationChanged(); break;
        case 2: _t->IsTriggerChanged(); break;
        case 3: _t->MaterialChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject SphereColliderComponentInspector::staticMetaObject = {
    { &ComponentInspector::staticMetaObject, qt_meta_stringdata_SphereColliderComponentInspector.data,
      qt_meta_data_SphereColliderComponentInspector,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SphereColliderComponentInspector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SphereColliderComponentInspector::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SphereColliderComponentInspector.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Observer"))
        return static_cast< Observer*>(this);
    return ComponentInspector::qt_metacast(_clname);
}

int SphereColliderComponentInspector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ComponentInspector::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
