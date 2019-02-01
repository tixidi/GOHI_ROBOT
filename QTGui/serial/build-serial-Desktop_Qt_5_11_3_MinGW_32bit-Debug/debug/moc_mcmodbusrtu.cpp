/****************************************************************************
** Meta object code from reading C++ file 'mcmodbusrtu.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../serial/mcmodbusrtu.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mcmodbusrtu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_McModbusRTU_t {
    QByteArrayData data[11];
    char stringdata0[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_McModbusRTU_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_McModbusRTU_t qt_meta_stringdata_McModbusRTU = {
    {
QT_MOC_LITERAL(0, 0, 11), // "McModbusRTU"
QT_MOC_LITERAL(1, 12, 18), // "McModbusRTUMessage"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 3), // "mID"
QT_MOC_LITERAL(4, 36, 9), // "mFunction"
QT_MOC_LITERAL(5, 46, 4), // "Data"
QT_MOC_LITERAL(6, 51, 8), // "response"
QT_MOC_LITERAL(7, 60, 1), // "s"
QT_MOC_LITERAL(8, 62, 9), // "response1"
QT_MOC_LITERAL(9, 72, 9), // "Read_Data"
QT_MOC_LITERAL(10, 82, 11) // "Tick_Server"

    },
    "McModbusRTU\0McModbusRTUMessage\0\0mID\0"
    "mFunction\0Data\0response\0s\0response1\0"
    "Read_Data\0Tick_Server"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_McModbusRTU[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   39,    2, 0x06 /* Public */,
       6,    1,   46,    2, 0x06 /* Public */,
       8,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   52,    2, 0x0a /* Public */,
      10,    0,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UChar, QMetaType::Int, QMetaType::QByteArray,    3,    4,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QByteArray,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void McModbusRTU::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        McModbusRTU *_t = static_cast<McModbusRTU *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->McModbusRTUMessage((*reinterpret_cast< unsigned char(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        case 1: _t->response((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->response1((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->Read_Data(); break;
        case 4: _t->Tick_Server(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (McModbusRTU::*)(unsigned char , int , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&McModbusRTU::McModbusRTUMessage)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (McModbusRTU::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&McModbusRTU::response)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (McModbusRTU::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&McModbusRTU::response1)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject McModbusRTU::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_McModbusRTU.data,
      qt_meta_data_McModbusRTU,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *McModbusRTU::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *McModbusRTU::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_McModbusRTU.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int McModbusRTU::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void McModbusRTU::McModbusRTUMessage(unsigned char _t1, int _t2, QByteArray _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void McModbusRTU::response(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void McModbusRTU::response1(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
