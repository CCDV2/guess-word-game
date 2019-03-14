/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GuessWordGame/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[16];
    char stringdata0[251];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 12), // "sendUserInfo"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 6), // "Player"
QT_MOC_LITERAL(4, 32, 6), // "player"
QT_MOC_LITERAL(5, 39, 10), // "Questioner"
QT_MOC_LITERAL(6, 50, 10), // "questioner"
QT_MOC_LITERAL(7, 61, 18), // "sendUpdateUserInfo"
QT_MOC_LITERAL(8, 80, 15), // "receiveUserInfo"
QT_MOC_LITERAL(9, 96, 7), // "_player"
QT_MOC_LITERAL(10, 104, 11), // "_questioner"
QT_MOC_LITERAL(11, 116, 25), // "receiveRequireForUserInfo"
QT_MOC_LITERAL(12, 142, 26), // "on_startGameButton_clicked"
QT_MOC_LITERAL(13, 169, 30), // "on_startQuestionButton_clicked"
QT_MOC_LITERAL(14, 200, 30), // "on_startRanklistButton_clicked"
QT_MOC_LITERAL(15, 231, 19) // "backToWelcomeWidget"

    },
    "MainWindow\0sendUserInfo\0\0Player\0player\0"
    "Questioner\0questioner\0sendUpdateUserInfo\0"
    "receiveUserInfo\0_player\0_questioner\0"
    "receiveRequireForUserInfo\0"
    "on_startGameButton_clicked\0"
    "on_startQuestionButton_clicked\0"
    "on_startRanklistButton_clicked\0"
    "backToWelcomeWidget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       7,    2,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    2,   64,    2, 0x0a /* Public */,
      11,    0,   69,    2, 0x0a /* Public */,
      12,    0,   70,    2, 0x08 /* Private */,
      13,    0,   71,    2, 0x08 /* Private */,
      14,    0,   72,    2, 0x08 /* Private */,
      15,    0,   73,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    9,   10,
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
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendUserInfo((*reinterpret_cast< Player(*)>(_a[1])),(*reinterpret_cast< Questioner(*)>(_a[2]))); break;
        case 1: _t->sendUpdateUserInfo((*reinterpret_cast< Player(*)>(_a[1])),(*reinterpret_cast< Questioner(*)>(_a[2]))); break;
        case 2: _t->receiveUserInfo((*reinterpret_cast< Player(*)>(_a[1])),(*reinterpret_cast< Questioner(*)>(_a[2]))); break;
        case 3: _t->receiveRequireForUserInfo(); break;
        case 4: _t->on_startGameButton_clicked(); break;
        case 5: _t->on_startQuestionButton_clicked(); break;
        case 6: _t->on_startRanklistButton_clicked(); break;
        case 7: _t->backToWelcomeWidget(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(Player , Questioner );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sendUserInfo)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(Player , Questioner );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sendUpdateUserInfo)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


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

// SIGNAL 0
void MainWindow::sendUserInfo(Player _t1, Questioner _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::sendUpdateUserInfo(Player _t1, Questioner _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
