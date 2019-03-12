/****************************************************************************
** Meta object code from reading C++ file 'ranklistwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GuessWordGame/ranklistwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ranklistwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RanklistWidget_t {
    QByteArrayData data[11];
    char stringdata0[181];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RanklistWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RanklistWidget_t qt_meta_stringdata_RanklistWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "RanklistWidget"
QT_MOC_LITERAL(1, 15, 15), // "requestRanklist"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 12), // "isPlayerList"
QT_MOC_LITERAL(4, 45, 15), // "receiveRanklist"
QT_MOC_LITERAL(5, 61, 15), // "QVector<Player>"
QT_MOC_LITERAL(6, 77, 7), // "players"
QT_MOC_LITERAL(7, 85, 19), // "QVector<Questioner>"
QT_MOC_LITERAL(8, 105, 11), // "questioners"
QT_MOC_LITERAL(9, 117, 29), // "on_searchPlayerButton_clicked"
QT_MOC_LITERAL(10, 147, 33) // "on_searchQuestionerButton_cli..."

    },
    "RanklistWidget\0requestRanklist\0\0"
    "isPlayerList\0receiveRanklist\0"
    "QVector<Player>\0players\0QVector<Questioner>\0"
    "questioners\0on_searchPlayerButton_clicked\0"
    "on_searchQuestionerButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RanklistWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    3,   37,    2, 0x0a /* Public */,
       9,    0,   44,    2, 0x08 /* Private */,
      10,    0,   45,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 7, QMetaType::Bool,    6,    8,    3,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RanklistWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RanklistWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->requestRanklist((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->receiveRanklist((*reinterpret_cast< QVector<Player>(*)>(_a[1])),(*reinterpret_cast< QVector<Questioner>(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 2: _t->on_searchPlayerButton_clicked(); break;
        case 3: _t->on_searchQuestionerButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RanklistWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RanklistWidget::requestRanklist)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RanklistWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_RanklistWidget.data,
    qt_meta_data_RanklistWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RanklistWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RanklistWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RanklistWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int RanklistWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void RanklistWidget::requestRanklist(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
