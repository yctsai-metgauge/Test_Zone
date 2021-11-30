/****************************************************************************
** Meta object code from reading C++ file 'new_tcp_thread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../check_tcp/new_tcp_thread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'new_tcp_thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_new_tcp_thread_t {
    QByteArrayData data[57];
    char stringdata0[873];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_new_tcp_thread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_new_tcp_thread_t qt_meta_stringdata_new_tcp_thread = {
    {
QT_MOC_LITERAL(0, 0, 14), // "new_tcp_thread"
QT_MOC_LITERAL(1, 15, 18), // "tcp_thread_connect"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 7), // "address"
QT_MOC_LITERAL(4, 43, 4), // "port"
QT_MOC_LITERAL(5, 48, 21), // "tcp_thread_disconnect"
QT_MOC_LITERAL(6, 70, 5), // "error"
QT_MOC_LITERAL(7, 76, 11), // "socketError"
QT_MOC_LITERAL(8, 88, 7), // "message"
QT_MOC_LITERAL(9, 96, 17), // "sendBackTempValue"
QT_MOC_LITERAL(10, 114, 7), // "double*"
QT_MOC_LITERAL(11, 122, 16), // "sendBackCboxTemp"
QT_MOC_LITERAL(12, 139, 15), // "sendBackAirFlow"
QT_MOC_LITERAL(13, 155, 11), // "sendBackPWM"
QT_MOC_LITERAL(14, 167, 11), // "PWM_Struct*"
QT_MOC_LITERAL(15, 179, 12), // "sendBackPyro"
QT_MOC_LITERAL(16, 192, 16), // "sendBackDiameter"
QT_MOC_LITERAL(17, 209, 6), // "float*"
QT_MOC_LITERAL(18, 216, 15), // "sendXYZDiameter"
QT_MOC_LITERAL(19, 232, 14), // "sendXYDiameter"
QT_MOC_LITERAL(20, 247, 18), // "sendBackXYDiameter"
QT_MOC_LITERAL(21, 266, 19), // "sendBackXYZDiameter"
QT_MOC_LITERAL(22, 286, 13), // "sendBackSpeed"
QT_MOC_LITERAL(23, 300, 17), // "sendRunningSignal"
QT_MOC_LITERAL(24, 318, 13), // "sendPyrometer"
QT_MOC_LITERAL(25, 332, 9), // "sendOffet"
QT_MOC_LITERAL(26, 342, 13), // "sendBackOffet"
QT_MOC_LITERAL(27, 356, 11), // "onConnected"
QT_MOC_LITERAL(28, 368, 14), // "onDisconnected"
QT_MOC_LITERAL(29, 383, 19), // "onSocketStateChange"
QT_MOC_LITERAL(30, 403, 28), // "QAbstractSocket::SocketState"
QT_MOC_LITERAL(31, 432, 11), // "socketState"
QT_MOC_LITERAL(32, 444, 23), // "Tempe_onSocketReadyRead"
QT_MOC_LITERAL(33, 468, 21), // "Cmd_onSocketReadyRead"
QT_MOC_LITERAL(34, 490, 17), // "Laser1_SocketRead"
QT_MOC_LITERAL(35, 508, 17), // "Laser2_SocketRead"
QT_MOC_LITERAL(36, 526, 28), // "Laser_onSocketReadyRead_Wire"
QT_MOC_LITERAL(37, 555, 27), // "Pyrometer_onSocketReadyRead"
QT_MOC_LITERAL(38, 583, 26), // "CBox_Cmd_onSocketReadyRead"
QT_MOC_LITERAL(39, 610, 36), // "CBox_Maf_and_Speed_onSocketRe..."
QT_MOC_LITERAL(40, 647, 29), // "CBox_Switch_onSocketReadyRead"
QT_MOC_LITERAL(41, 677, 11), // "getPWMValue"
QT_MOC_LITERAL(42, 689, 14), // "getXYZDiameter"
QT_MOC_LITERAL(43, 704, 12), // "getPyrometer"
QT_MOC_LITERAL(44, 717, 18), // "getExtSignalConfig"
QT_MOC_LITERAL(45, 736, 16), // "External_signal*"
QT_MOC_LITERAL(46, 753, 17), // "getResetExtSignal"
QT_MOC_LITERAL(47, 771, 12), // "getLV1Signal"
QT_MOC_LITERAL(48, 784, 8), // "getLV1S1"
QT_MOC_LITERAL(49, 793, 8), // "getLV1S2"
QT_MOC_LITERAL(50, 802, 8), // "getLV1S3"
QT_MOC_LITERAL(51, 811, 8), // "getLV1S4"
QT_MOC_LITERAL(52, 820, 7), // "getUnit"
QT_MOC_LITERAL(53, 828, 9), // "UNIT_Type"
QT_MOC_LITERAL(54, 838, 12), // "getTibboFlag"
QT_MOC_LITERAL(55, 851, 11), // "getTHSensor"
QT_MOC_LITERAL(56, 863, 9) // "getOffset"

    },
    "new_tcp_thread\0tcp_thread_connect\0\0"
    "address\0port\0tcp_thread_disconnect\0"
    "error\0socketError\0message\0sendBackTempValue\0"
    "double*\0sendBackCboxTemp\0sendBackAirFlow\0"
    "sendBackPWM\0PWM_Struct*\0sendBackPyro\0"
    "sendBackDiameter\0float*\0sendXYZDiameter\0"
    "sendXYDiameter\0sendBackXYDiameter\0"
    "sendBackXYZDiameter\0sendBackSpeed\0"
    "sendRunningSignal\0sendPyrometer\0"
    "sendOffet\0sendBackOffet\0onConnected\0"
    "onDisconnected\0onSocketStateChange\0"
    "QAbstractSocket::SocketState\0socketState\0"
    "Tempe_onSocketReadyRead\0Cmd_onSocketReadyRead\0"
    "Laser1_SocketRead\0Laser2_SocketRead\0"
    "Laser_onSocketReadyRead_Wire\0"
    "Pyrometer_onSocketReadyRead\0"
    "CBox_Cmd_onSocketReadyRead\0"
    "CBox_Maf_and_Speed_onSocketReadyRead\0"
    "CBox_Switch_onSocketReadyRead\0getPWMValue\0"
    "getXYZDiameter\0getPyrometer\0"
    "getExtSignalConfig\0External_signal*\0"
    "getResetExtSignal\0getLV1Signal\0getLV1S1\0"
    "getLV1S2\0getLV1S3\0getLV1S4\0getUnit\0"
    "UNIT_Type\0getTibboFlag\0getTHSensor\0"
    "getOffset"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_new_tcp_thread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      44,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      18,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  234,    2, 0x06 /* Public */,
       5,    2,  239,    2, 0x06 /* Public */,
       6,    2,  244,    2, 0x06 /* Public */,
       9,    2,  249,    2, 0x06 /* Public */,
      11,    2,  254,    2, 0x06 /* Public */,
      12,    1,  259,    2, 0x06 /* Public */,
      13,    1,  262,    2, 0x06 /* Public */,
      15,    1,  265,    2, 0x06 /* Public */,
      16,    1,  268,    2, 0x06 /* Public */,
      18,    1,  271,    2, 0x06 /* Public */,
      19,    1,  274,    2, 0x06 /* Public */,
      20,    1,  277,    2, 0x06 /* Public */,
      21,    1,  280,    2, 0x06 /* Public */,
      22,    1,  283,    2, 0x06 /* Public */,
      23,    1,  286,    2, 0x06 /* Public */,
      24,    1,  289,    2, 0x06 /* Public */,
      25,    1,  292,    2, 0x06 /* Public */,
      26,    1,  295,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      27,    0,  298,    2, 0x08 /* Private */,
      28,    0,  299,    2, 0x08 /* Private */,
      29,    1,  300,    2, 0x08 /* Private */,
      32,    0,  303,    2, 0x08 /* Private */,
      33,    0,  304,    2, 0x08 /* Private */,
      34,    0,  305,    2, 0x08 /* Private */,
      35,    0,  306,    2, 0x08 /* Private */,
      36,    0,  307,    2, 0x08 /* Private */,
      37,    0,  308,    2, 0x08 /* Private */,
      38,    0,  309,    2, 0x08 /* Private */,
      39,    0,  310,    2, 0x08 /* Private */,
      40,    0,  311,    2, 0x08 /* Private */,
      41,    1,  312,    2, 0x08 /* Private */,
      42,    1,  315,    2, 0x08 /* Private */,
      43,    1,  318,    2, 0x08 /* Private */,
      44,    1,  321,    2, 0x08 /* Private */,
      46,    1,  324,    2, 0x08 /* Private */,
      47,    4,  327,    2, 0x08 /* Private */,
      48,    1,  336,    2, 0x08 /* Private */,
      49,    1,  339,    2, 0x08 /* Private */,
      50,    1,  342,    2, 0x08 /* Private */,
      51,    1,  345,    2, 0x08 /* Private */,
      52,    1,  348,    2, 0x08 /* Private */,
      54,    1,  351,    2, 0x08 /* Private */,
      55,    1,  354,    2, 0x08 /* Private */,
      56,    1,  357,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    7,    8,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 10,    2,    2,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 10,    2,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, 0x80000000 | 14,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, 0x80000000 | 17,    2,
    QMetaType::Void, 0x80000000 | 17,    2,
    QMetaType::Void, 0x80000000 | 17,    2,
    QMetaType::Void, 0x80000000 | 17,    2,
    QMetaType::Void, 0x80000000 | 17,    2,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QReal,    2,
    QMetaType::Void, 0x80000000 | 17,    2,
    QMetaType::Void, 0x80000000 | 17,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 30,   31,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,    2,
    QMetaType::Void, 0x80000000 | 17,    2,
    QMetaType::Void, QMetaType::QReal,    2,
    QMetaType::Void, 0x80000000 | 45,    2,
    QMetaType::Void, 0x80000000 | 45,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, 0x80000000 | 53,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 17,    2,

       0        // eod
};

void new_tcp_thread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<new_tcp_thread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->tcp_thread_connect((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->tcp_thread_disconnect((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->error((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->sendBackTempValue((*reinterpret_cast< double*(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2]))); break;
        case 4: _t->sendBackCboxTemp((*reinterpret_cast< double*(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2]))); break;
        case 5: _t->sendBackAirFlow((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->sendBackPWM((*reinterpret_cast< PWM_Struct*(*)>(_a[1]))); break;
        case 7: _t->sendBackPyro((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->sendBackDiameter((*reinterpret_cast< float*(*)>(_a[1]))); break;
        case 9: _t->sendXYZDiameter((*reinterpret_cast< float*(*)>(_a[1]))); break;
        case 10: _t->sendXYDiameter((*reinterpret_cast< float*(*)>(_a[1]))); break;
        case 11: _t->sendBackXYDiameter((*reinterpret_cast< float*(*)>(_a[1]))); break;
        case 12: _t->sendBackXYZDiameter((*reinterpret_cast< float*(*)>(_a[1]))); break;
        case 13: _t->sendBackSpeed((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 14: _t->sendRunningSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->sendPyrometer((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 16: _t->sendOffet((*reinterpret_cast< float*(*)>(_a[1]))); break;
        case 17: _t->sendBackOffet((*reinterpret_cast< float*(*)>(_a[1]))); break;
        case 18: _t->onConnected(); break;
        case 19: _t->onDisconnected(); break;
        case 20: _t->onSocketStateChange((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        case 21: _t->Tempe_onSocketReadyRead(); break;
        case 22: _t->Cmd_onSocketReadyRead(); break;
        case 23: _t->Laser1_SocketRead(); break;
        case 24: _t->Laser2_SocketRead(); break;
        case 25: _t->Laser_onSocketReadyRead_Wire(); break;
        case 26: _t->Pyrometer_onSocketReadyRead(); break;
        case 27: _t->CBox_Cmd_onSocketReadyRead(); break;
        case 28: _t->CBox_Maf_and_Speed_onSocketReadyRead(); break;
        case 29: _t->CBox_Switch_onSocketReadyRead(); break;
        case 30: _t->getPWMValue((*reinterpret_cast< PWM_Struct*(*)>(_a[1]))); break;
        case 31: _t->getXYZDiameter((*reinterpret_cast< float*(*)>(_a[1]))); break;
        case 32: _t->getPyrometer((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 33: _t->getExtSignalConfig((*reinterpret_cast< External_signal*(*)>(_a[1]))); break;
        case 34: _t->getResetExtSignal((*reinterpret_cast< External_signal*(*)>(_a[1]))); break;
        case 35: _t->getLV1Signal((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 36: _t->getLV1S1((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 37: _t->getLV1S2((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 38: _t->getLV1S3((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 39: _t->getLV1S4((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 40: _t->getUnit((*reinterpret_cast< UNIT_Type(*)>(_a[1]))); break;
        case 41: _t->getTibboFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 42: _t->getTHSensor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 43: _t->getOffset((*reinterpret_cast< float*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 20:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketState >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (new_tcp_thread::*)(QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&new_tcp_thread::tcp_thread_connect)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (new_tcp_thread::*)(QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&new_tcp_thread::tcp_thread_disconnect)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (new_tcp_thread::*)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&new_tcp_thread::error)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (new_tcp_thread::*)(double * , double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&new_tcp_thread::sendBackTempValue)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (new_tcp_thread::*)(double * , double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&new_tcp_thread::sendBackCboxTemp)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (new_tcp_thread::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&new_tcp_thread::sendBackAirFlow)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (new_tcp_thread::*)(PWM_Struct * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&new_tcp_thread::sendBackPWM)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (new_tcp_thread::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&new_tcp_thread::sendBackPyro)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (new_tcp_thread::*)(float * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&new_tcp_thread::sendBackDiameter)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (new_tcp_thread::*)(float * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&new_tcp_thread::sendXYZDiameter)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (new_tcp_thread::*)(float * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&new_tcp_thread::sendXYDiameter)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (new_tcp_thread::*)(float * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&new_tcp_thread::sendBackXYDiameter)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (new_tcp_thread::*)(float * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&new_tcp_thread::sendBackXYZDiameter)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (new_tcp_thread::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&new_tcp_thread::sendBackSpeed)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (new_tcp_thread::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&new_tcp_thread::sendRunningSignal)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (new_tcp_thread::*)(qreal );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&new_tcp_thread::sendPyrometer)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (new_tcp_thread::*)(float * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&new_tcp_thread::sendOffet)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (new_tcp_thread::*)(float * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&new_tcp_thread::sendBackOffet)) {
                *result = 17;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject new_tcp_thread::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_new_tcp_thread.data,
    qt_meta_data_new_tcp_thread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *new_tcp_thread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *new_tcp_thread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_new_tcp_thread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int new_tcp_thread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 44)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 44;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 44)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 44;
    }
    return _id;
}

// SIGNAL 0
void new_tcp_thread::tcp_thread_connect(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void new_tcp_thread::tcp_thread_disconnect(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void new_tcp_thread::error(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void new_tcp_thread::sendBackTempValue(double * _t1, double * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void new_tcp_thread::sendBackCboxTemp(double * _t1, double * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void new_tcp_thread::sendBackAirFlow(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void new_tcp_thread::sendBackPWM(PWM_Struct * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void new_tcp_thread::sendBackPyro(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void new_tcp_thread::sendBackDiameter(float * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void new_tcp_thread::sendXYZDiameter(float * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void new_tcp_thread::sendXYDiameter(float * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void new_tcp_thread::sendBackXYDiameter(float * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void new_tcp_thread::sendBackXYZDiameter(float * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void new_tcp_thread::sendBackSpeed(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void new_tcp_thread::sendRunningSignal(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void new_tcp_thread::sendPyrometer(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void new_tcp_thread::sendOffet(float * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void new_tcp_thread::sendBackOffet(float * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
