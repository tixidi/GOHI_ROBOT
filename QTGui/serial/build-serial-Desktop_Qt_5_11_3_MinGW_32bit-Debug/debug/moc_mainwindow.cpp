/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../serial/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[28];
    char stringdata0[451];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 10), // "signalThis"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 11), // "MainWindow*"
QT_MOC_LITERAL(4, 35, 12), // "testPointNum"
QT_MOC_LITERAL(5, 48, 10), // "QList<int>"
QT_MOC_LITERAL(6, 59, 14), // "testPointValue"
QT_MOC_LITERAL(7, 74, 14), // "QList<RowData>"
QT_MOC_LITERAL(8, 89, 7), // "exitApp"
QT_MOC_LITERAL(9, 97, 5), // "click"
QT_MOC_LITERAL(10, 103, 14), // "openSerialPort"
QT_MOC_LITERAL(11, 118, 15), // "closeSerialPort"
QT_MOC_LITERAL(12, 134, 16), // "clearReceiveArea"
QT_MOC_LITERAL(13, 151, 16), // "timeToReadSensor"
QT_MOC_LITERAL(14, 168, 15), // "timeToReadLaser"
QT_MOC_LITERAL(15, 184, 11), // "handleError"
QT_MOC_LITERAL(16, 196, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(17, 225, 5), // "error"
QT_MOC_LITERAL(18, 231, 12), // "showResponse"
QT_MOC_LITERAL(19, 244, 1), // "s"
QT_MOC_LITERAL(20, 246, 16), // "showResponseToUI"
QT_MOC_LITERAL(21, 263, 30), // "on_dataTablePushButton_clicked"
QT_MOC_LITERAL(22, 294, 32), // "on_dataTablePushButton_2_clicked"
QT_MOC_LITERAL(23, 327, 22), // "sendCar1ControlCommand"
QT_MOC_LITERAL(24, 350, 22), // "sendCar3ControlCommand"
QT_MOC_LITERAL(25, 373, 22), // "sendCar4ControlCommand"
QT_MOC_LITERAL(26, 396, 25), // "sendWriteIDControlCommand"
QT_MOC_LITERAL(27, 422, 28) // "sendLaserRangeControlCommand"

    },
    "MainWindow\0signalThis\0\0MainWindow*\0"
    "testPointNum\0QList<int>\0testPointValue\0"
    "QList<RowData>\0exitApp\0click\0"
    "openSerialPort\0closeSerialPort\0"
    "clearReceiveArea\0timeToReadSensor\0"
    "timeToReadLaser\0handleError\0"
    "QSerialPort::SerialPortError\0error\0"
    "showResponse\0s\0showResponseToUI\0"
    "on_dataTablePushButton_clicked\0"
    "on_dataTablePushButton_2_clicked\0"
    "sendCar1ControlCommand\0sendCar3ControlCommand\0"
    "sendCar4ControlCommand\0sendWriteIDControlCommand\0"
    "sendLaserRangeControlCommand"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  109,    2, 0x06 /* Public */,
       4,    1,  112,    2, 0x06 /* Public */,
       6,    1,  115,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,  118,    2, 0x0a /* Public */,
      10,    0,  121,    2, 0x08 /* Private */,
      11,    0,  122,    2, 0x08 /* Private */,
      12,    0,  123,    2, 0x08 /* Private */,
      13,    0,  124,    2, 0x08 /* Private */,
      14,    0,  125,    2, 0x08 /* Private */,
      15,    1,  126,    2, 0x08 /* Private */,
      18,    1,  129,    2, 0x08 /* Private */,
      20,    1,  132,    2, 0x08 /* Private */,
      21,    0,  135,    2, 0x08 /* Private */,
      22,    0,  136,    2, 0x08 /* Private */,
      23,    0,  137,    2, 0x08 /* Private */,
      24,    0,  138,    2, 0x08 /* Private */,
      25,    0,  139,    2, 0x08 /* Private */,
      26,    0,  140,    2, 0x08 /* Private */,
      27,    0,  141,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 7,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void, QMetaType::QByteArray,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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
        case 0: _t->signalThis((*reinterpret_cast< MainWindow*(*)>(_a[1]))); break;
        case 1: _t->testPointNum((*reinterpret_cast< QList<int>(*)>(_a[1]))); break;
        case 2: _t->testPointValue((*reinterpret_cast< QList<RowData>(*)>(_a[1]))); break;
        case 3: _t->exitApp((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->openSerialPort(); break;
        case 5: _t->closeSerialPort(); break;
        case 6: _t->clearReceiveArea(); break;
        case 7: _t->timeToReadSensor(); break;
        case 8: _t->timeToReadLaser(); break;
        case 9: _t->handleError((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 10: _t->showResponse((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->showResponseToUI((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 12: _t->on_dataTablePushButton_clicked(); break;
        case 13: _t->on_dataTablePushButton_2_clicked(); break;
        case 14: _t->sendCar1ControlCommand(); break;
        case 15: _t->sendCar3ControlCommand(); break;
        case 16: _t->sendCar4ControlCommand(); break;
        case 17: _t->sendWriteIDControlCommand(); break;
        case 18: _t->sendLaserRangeControlCommand(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< MainWindow* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<int> >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<RowData> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(MainWindow * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::signalThis)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QList<int> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::testPointNum)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QList<RowData> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::testPointValue)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::signalThis(MainWindow * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::testPointNum(QList<int> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::testPointValue(QList<RowData> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
