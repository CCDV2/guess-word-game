/****************************************************************************
** Meta object code from reading C++ file 'databaseserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GuessWordGame/databaseserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'databaseserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DatabaseServer_t {
    QByteArrayData data[29];
    char stringdata0[390];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DatabaseServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DatabaseServer_t qt_meta_stringdata_DatabaseServer = {
    {
QT_MOC_LITERAL(0, 0, 14), // "DatabaseServer"
QT_MOC_LITERAL(1, 15, 14), // "sendLoginState"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 10), // "LoginState"
QT_MOC_LITERAL(4, 42, 5), // "state"
QT_MOC_LITERAL(5, 48, 17), // "sendRegisterState"
QT_MOC_LITERAL(6, 66, 13), // "RegisterState"
QT_MOC_LITERAL(7, 80, 12), // "sendUserInfo"
QT_MOC_LITERAL(8, 93, 6), // "Player"
QT_MOC_LITERAL(9, 100, 6), // "player"
QT_MOC_LITERAL(10, 107, 10), // "Questioner"
QT_MOC_LITERAL(11, 118, 10), // "questioner"
QT_MOC_LITERAL(12, 129, 12), // "sendRanklist"
QT_MOC_LITERAL(13, 142, 15), // "QVector<Player>"
QT_MOC_LITERAL(14, 158, 7), // "players"
QT_MOC_LITERAL(15, 166, 19), // "QVector<Questioner>"
QT_MOC_LITERAL(16, 186, 11), // "questioners"
QT_MOC_LITERAL(17, 198, 10), // "SortMethod"
QT_MOC_LITERAL(18, 209, 10), // "sortMethod"
QT_MOC_LITERAL(19, 220, 14), // "sendDetailInfo"
QT_MOC_LITERAL(20, 235, 19), // "receiveLoginPackage"
QT_MOC_LITERAL(21, 255, 12), // "LoginPackage"
QT_MOC_LITERAL(22, 268, 12), // "loginPackage"
QT_MOC_LITERAL(23, 281, 22), // "receiveRegisterPackage"
QT_MOC_LITERAL(24, 304, 15), // "RegisterPackage"
QT_MOC_LITERAL(25, 320, 15), // "registerPackage"
QT_MOC_LITERAL(26, 336, 22), // "receiveRanklistRequest"
QT_MOC_LITERAL(27, 359, 24), // "receiveDetailInfoRequest"
QT_MOC_LITERAL(28, 384, 5) // "index"

    },
    "DatabaseServer\0sendLoginState\0\0"
    "LoginState\0state\0sendRegisterState\0"
    "RegisterState\0sendUserInfo\0Player\0"
    "player\0Questioner\0questioner\0sendRanklist\0"
    "QVector<Player>\0players\0QVector<Questioner>\0"
    "questioners\0SortMethod\0sortMethod\0"
    "sendDetailInfo\0receiveLoginPackage\0"
    "LoginPackage\0loginPackage\0"
    "receiveRegisterPackage\0RegisterPackage\0"
    "registerPackage\0receiveRanklistRequest\0"
    "receiveDetailInfoRequest\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DatabaseServer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       5,    1,   62,    2, 0x06 /* Public */,
       7,    2,   65,    2, 0x06 /* Public */,
      12,    3,   70,    2, 0x06 /* Public */,
      19,    2,   77,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      20,    1,   82,    2, 0x0a /* Public */,
      23,    1,   85,    2, 0x0a /* Public */,
      26,    1,   88,    2, 0x0a /* Public */,
      27,    2,   91,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    4,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 10,    9,   11,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 15, 0x80000000 | 17,   14,   16,   18,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 10,    9,   11,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void, 0x80000000 | 24,   25,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 17, QMetaType::Int,   18,   28,

       0        // eod
};

void DatabaseServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DatabaseServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendLoginState((*reinterpret_cast< LoginState(*)>(_a[1]))); break;
        case 1: _t->sendRegisterState((*reinterpret_cast< RegisterState(*)>(_a[1]))); break;
        case 2: _t->sendUserInfo((*reinterpret_cast< Player(*)>(_a[1])),(*reinterpret_cast< Questioner(*)>(_a[2]))); break;
        case 3: _t->sendRanklist((*reinterpret_cast< QVector<Player>(*)>(_a[1])),(*reinterpret_cast< QVector<Questioner>(*)>(_a[2])),(*reinterpret_cast< SortMethod(*)>(_a[3]))); break;
        case 4: _t->sendDetailInfo((*reinterpret_cast< Player(*)>(_a[1])),(*reinterpret_cast< Questioner(*)>(_a[2]))); break;
        case 5: _t->receiveLoginPackage((*reinterpret_cast< LoginPackage(*)>(_a[1]))); break;
        case 6: _t->receiveRegisterPackage((*reinterpret_cast< RegisterPackage(*)>(_a[1]))); break;
        case 7: _t->receiveRanklistRequest((*reinterpret_cast< SortMethod(*)>(_a[1]))); break;
        case 8: _t->receiveDetailInfoRequest((*reinterpret_cast< SortMethod(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DatabaseServer::*)(LoginState );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DatabaseServer::sendLoginState)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DatabaseServer::*)(RegisterState );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DatabaseServer::sendRegisterState)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DatabaseServer::*)(Player , Questioner );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DatabaseServer::sendUserInfo)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DatabaseServer::*)(QVector<Player> , QVector<Questioner> , SortMethod );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DatabaseServer::sendRanklist)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (DatabaseServer::*)(Player , Questioner );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DatabaseServer::sendDetailInfo)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DatabaseServer::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_DatabaseServer.data,
    qt_meta_data_DatabaseServer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DatabaseServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DatabaseServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DatabaseServer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DatabaseServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void DatabaseServer::sendLoginState(LoginState _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DatabaseServer::sendRegisterState(RegisterState _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DatabaseServer::sendUserInfo(Player _t1, Questioner _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DatabaseServer::sendRanklist(QVector<Player> _t1, QVector<Questioner> _t2, SortMethod _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DatabaseServer::sendDetailInfo(Player _t1, Questioner _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
