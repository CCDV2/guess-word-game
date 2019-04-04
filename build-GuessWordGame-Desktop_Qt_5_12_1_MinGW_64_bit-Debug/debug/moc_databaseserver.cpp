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
    QByteArrayData data[42];
    char stringdata0[557];
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
QT_MOC_LITERAL(20, 235, 12), // "sendWordList"
QT_MOC_LITERAL(21, 248, 13), // "QVector<Word>"
QT_MOC_LITERAL(22, 262, 5), // "words"
QT_MOC_LITERAL(23, 268, 14), // "sendAddedWords"
QT_MOC_LITERAL(24, 283, 5), // "count"
QT_MOC_LITERAL(25, 289, 9), // "expGained"
QT_MOC_LITERAL(26, 299, 19), // "receiveLoginPackage"
QT_MOC_LITERAL(27, 319, 12), // "LoginPackage"
QT_MOC_LITERAL(28, 332, 12), // "loginPackage"
QT_MOC_LITERAL(29, 345, 22), // "receiveRegisterPackage"
QT_MOC_LITERAL(30, 368, 15), // "RegisterPackage"
QT_MOC_LITERAL(31, 384, 15), // "registerPackage"
QT_MOC_LITERAL(32, 400, 22), // "receiveRanklistRequest"
QT_MOC_LITERAL(33, 423, 24), // "receiveDetailInfoRequest"
QT_MOC_LITERAL(34, 448, 5), // "index"
QT_MOC_LITERAL(35, 454, 22), // "receiveWordListRequest"
QT_MOC_LITERAL(36, 477, 9), // "GameLevel"
QT_MOC_LITERAL(37, 487, 5), // "level"
QT_MOC_LITERAL(38, 493, 17), // "receiveUpdatedExp"
QT_MOC_LITERAL(39, 511, 10), // "playerName"
QT_MOC_LITERAL(40, 522, 10), // "problemNum"
QT_MOC_LITERAL(41, 533, 23) // "receiveQuestionWordList"

    },
    "DatabaseServer\0sendLoginState\0\0"
    "LoginState\0state\0sendRegisterState\0"
    "RegisterState\0sendUserInfo\0Player\0"
    "player\0Questioner\0questioner\0sendRanklist\0"
    "QVector<Player>\0players\0QVector<Questioner>\0"
    "questioners\0SortMethod\0sortMethod\0"
    "sendDetailInfo\0sendWordList\0QVector<Word>\0"
    "words\0sendAddedWords\0count\0expGained\0"
    "receiveLoginPackage\0LoginPackage\0"
    "loginPackage\0receiveRegisterPackage\0"
    "RegisterPackage\0registerPackage\0"
    "receiveRanklistRequest\0receiveDetailInfoRequest\0"
    "index\0receiveWordListRequest\0GameLevel\0"
    "level\0receiveUpdatedExp\0playerName\0"
    "problemNum\0receiveQuestionWordList"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DatabaseServer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       5,    1,   87,    2, 0x06 /* Public */,
       7,    2,   90,    2, 0x06 /* Public */,
      12,    3,   95,    2, 0x06 /* Public */,
      19,    2,  102,    2, 0x06 /* Public */,
      20,    1,  107,    2, 0x06 /* Public */,
      23,    2,  110,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      26,    1,  115,    2, 0x0a /* Public */,
      29,    1,  118,    2, 0x0a /* Public */,
      32,    1,  121,    2, 0x0a /* Public */,
      33,    2,  124,    2, 0x0a /* Public */,
      35,    1,  129,    2, 0x0a /* Public */,
      38,    3,  132,    2, 0x0a /* Public */,
      41,    2,  139,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    4,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 10,    9,   11,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 15, 0x80000000 | 17,   14,   16,   18,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 10,    9,   11,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   24,   25,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 27,   28,
    QMetaType::Void, 0x80000000 | 30,   31,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 17, QMetaType::Int,   18,   34,
    QMetaType::Void, 0x80000000 | 36,   37,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,   39,   25,   40,
    QMetaType::Void, 0x80000000 | 21, QMetaType::QString,   22,   11,

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
        case 5: _t->sendWordList((*reinterpret_cast< QVector<Word>(*)>(_a[1]))); break;
        case 6: _t->sendAddedWords((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->receiveLoginPackage((*reinterpret_cast< LoginPackage(*)>(_a[1]))); break;
        case 8: _t->receiveRegisterPackage((*reinterpret_cast< RegisterPackage(*)>(_a[1]))); break;
        case 9: _t->receiveRanklistRequest((*reinterpret_cast< SortMethod(*)>(_a[1]))); break;
        case 10: _t->receiveDetailInfoRequest((*reinterpret_cast< SortMethod(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->receiveWordListRequest((*reinterpret_cast< GameLevel(*)>(_a[1]))); break;
        case 12: _t->receiveUpdatedExp((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 13: _t->receiveQuestionWordList((*reinterpret_cast< QVector<Word>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
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
        {
            using _t = void (DatabaseServer::*)(QVector<Word> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DatabaseServer::sendWordList)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (DatabaseServer::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DatabaseServer::sendAddedWords)) {
                *result = 6;
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
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
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

// SIGNAL 5
void DatabaseServer::sendWordList(QVector<Word> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void DatabaseServer::sendAddedWords(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
