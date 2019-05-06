/****************************************************************************
** Meta object code from reading C++ file 'gamemodeselectwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GuessWordGame/gamemodeselectwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamemodeselectwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GameModeSelectWidget_t {
    QByteArrayData data[12];
    char stringdata0[173];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameModeSelectWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameModeSelectWidget_t qt_meta_stringdata_GameModeSelectWidget = {
    {
QT_MOC_LITERAL(0, 0, 20), // "GameModeSelectWidget"
QT_MOC_LITERAL(1, 21, 12), // "sendGameMode"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 9), // "GameLevel"
QT_MOC_LITERAL(4, 45, 5), // "level"
QT_MOC_LITERAL(5, 51, 10), // "paintEvent"
QT_MOC_LITERAL(6, 62, 12), // "QPaintEvent*"
QT_MOC_LITERAL(7, 75, 5), // "event"
QT_MOC_LITERAL(8, 81, 21), // "on_easyButton_clicked"
QT_MOC_LITERAL(9, 103, 23), // "on_normalButton_clicked"
QT_MOC_LITERAL(10, 127, 21), // "on_hardButton_clicked"
QT_MOC_LITERAL(11, 149, 23) // "on_expertButton_clicked"

    },
    "GameModeSelectWidget\0sendGameMode\0\0"
    "GameLevel\0level\0paintEvent\0QPaintEvent*\0"
    "event\0on_easyButton_clicked\0"
    "on_normalButton_clicked\0on_hardButton_clicked\0"
    "on_expertButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameModeSelectWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   47,    2, 0x0a /* Public */,
       8,    0,   50,    2, 0x08 /* Private */,
       9,    0,   51,    2, 0x08 /* Private */,
      10,    0,   52,    2, 0x08 /* Private */,
      11,    0,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GameModeSelectWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GameModeSelectWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendGameMode((*reinterpret_cast< GameLevel(*)>(_a[1]))); break;
        case 1: _t->paintEvent((*reinterpret_cast< QPaintEvent*(*)>(_a[1]))); break;
        case 2: _t->on_easyButton_clicked(); break;
        case 3: _t->on_normalButton_clicked(); break;
        case 4: _t->on_hardButton_clicked(); break;
        case 5: _t->on_expertButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GameModeSelectWidget::*)(GameLevel );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GameModeSelectWidget::sendGameMode)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GameModeSelectWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_GameModeSelectWidget.data,
    qt_meta_data_GameModeSelectWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GameModeSelectWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameModeSelectWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GameModeSelectWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GameModeSelectWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void GameModeSelectWidget::sendGameMode(GameLevel _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
