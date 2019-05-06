/****************************************************************************
** Meta object code from reading C++ file 'gamewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GuessWordGame/gamewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GameWidget_t {
    QByteArrayData data[23];
    char stringdata0[275];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameWidget_t qt_meta_stringdata_GameWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "GameWidget"
QT_MOC_LITERAL(1, 11, 15), // "requestWordList"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 9), // "GameLevel"
QT_MOC_LITERAL(4, 38, 5), // "level"
QT_MOC_LITERAL(5, 44, 18), // "wordCorrectChecked"
QT_MOC_LITERAL(6, 63, 9), // "isCorrect"
QT_MOC_LITERAL(7, 73, 13), // "updateUserExp"
QT_MOC_LITERAL(8, 87, 10), // "playerName"
QT_MOC_LITERAL(9, 98, 9), // "expGained"
QT_MOC_LITERAL(10, 108, 10), // "problemNum"
QT_MOC_LITERAL(11, 119, 12), // "toMainWindow"
QT_MOC_LITERAL(12, 132, 11), // "receiveWord"
QT_MOC_LITERAL(13, 144, 15), // "receiveWordList"
QT_MOC_LITERAL(14, 160, 13), // "QVector<Word>"
QT_MOC_LITERAL(15, 174, 6), // "_words"
QT_MOC_LITERAL(16, 181, 24), // "receiveShowEndGameDialog"
QT_MOC_LITERAL(17, 206, 10), // "paintEvent"
QT_MOC_LITERAL(18, 217, 12), // "QPaintEvent*"
QT_MOC_LITERAL(19, 230, 5), // "event"
QT_MOC_LITERAL(20, 236, 15), // "updateCountDown"
QT_MOC_LITERAL(21, 252, 8), // "nextWord"
QT_MOC_LITERAL(22, 261, 13) // "isLastCorrect"

    },
    "GameWidget\0requestWordList\0\0GameLevel\0"
    "level\0wordCorrectChecked\0isCorrect\0"
    "updateUserExp\0playerName\0expGained\0"
    "problemNum\0toMainWindow\0receiveWord\0"
    "receiveWordList\0QVector<Word>\0_words\0"
    "receiveShowEndGameDialog\0paintEvent\0"
    "QPaintEvent*\0event\0updateCountDown\0"
    "nextWord\0isLastCorrect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       5,    1,   67,    2, 0x06 /* Public */,
       7,    3,   70,    2, 0x06 /* Public */,
      11,    0,   77,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,   78,    2, 0x0a /* Public */,
      13,    1,   81,    2, 0x0a /* Public */,
      16,    0,   84,    2, 0x0a /* Public */,
      17,    1,   85,    2, 0x0a /* Public */,
      20,    0,   88,    2, 0x08 /* Private */,
      21,    1,   89,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,    8,    9,   10,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   22,

       0        // eod
};

void GameWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GameWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->requestWordList((*reinterpret_cast< GameLevel(*)>(_a[1]))); break;
        case 1: _t->wordCorrectChecked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->updateUserExp((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->toMainWindow(); break;
        case 4: _t->receiveWord((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->receiveWordList((*reinterpret_cast< QVector<Word>(*)>(_a[1]))); break;
        case 6: _t->receiveShowEndGameDialog(); break;
        case 7: _t->paintEvent((*reinterpret_cast< QPaintEvent*(*)>(_a[1]))); break;
        case 8: _t->updateCountDown(); break;
        case 9: _t->nextWord((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GameWidget::*)(GameLevel );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameWidget::requestWordList)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GameWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameWidget::wordCorrectChecked)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GameWidget::*)(QString , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameWidget::updateUserExp)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GameWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameWidget::toMainWindow)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GameWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_GameWidget.data,
    qt_meta_data_GameWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GameWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GameWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GameWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void GameWidget::requestWordList(GameLevel _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GameWidget::wordCorrectChecked(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GameWidget::updateUserExp(QString _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GameWidget::toMainWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
struct qt_meta_stringdata_WordLineEdit_t {
    QByteArrayData data[5];
    char stringdata0[48];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WordLineEdit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WordLineEdit_t qt_meta_stringdata_WordLineEdit = {
    {
QT_MOC_LITERAL(0, 0, 12), // "WordLineEdit"
QT_MOC_LITERAL(1, 13, 8), // "sendWord"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 13), // "keyPressEvent"
QT_MOC_LITERAL(4, 37, 10) // "QKeyEvent*"

    },
    "WordLineEdit\0sendWord\0\0keyPressEvent\0"
    "QKeyEvent*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WordLineEdit[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   27,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    2,

       0        // eod
};

void WordLineEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WordLineEdit *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendWord((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WordLineEdit::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WordLineEdit::sendWord)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WordLineEdit::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_WordLineEdit.data,
    qt_meta_data_WordLineEdit,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WordLineEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WordLineEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WordLineEdit.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int WordLineEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void WordLineEdit::sendWord(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
