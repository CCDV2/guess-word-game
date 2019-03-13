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
    QByteArrayData data[24];
    char stringdata0[349];
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
QT_MOC_LITERAL(3, 32, 10), // "SortMethod"
QT_MOC_LITERAL(4, 43, 10), // "sortMethod"
QT_MOC_LITERAL(5, 54, 17), // "requestDetailInfo"
QT_MOC_LITERAL(6, 72, 5), // "index"
QT_MOC_LITERAL(7, 78, 15), // "receiveRanklist"
QT_MOC_LITERAL(8, 94, 15), // "QVector<Player>"
QT_MOC_LITERAL(9, 110, 7), // "players"
QT_MOC_LITERAL(10, 118, 19), // "QVector<Questioner>"
QT_MOC_LITERAL(11, 138, 11), // "questioners"
QT_MOC_LITERAL(12, 150, 17), // "receiveDetailInfo"
QT_MOC_LITERAL(13, 168, 6), // "Player"
QT_MOC_LITERAL(14, 175, 6), // "player"
QT_MOC_LITERAL(15, 182, 10), // "Questioner"
QT_MOC_LITERAL(16, 193, 10), // "questioner"
QT_MOC_LITERAL(17, 204, 29), // "on_searchPlayerButton_clicked"
QT_MOC_LITERAL(18, 234, 33), // "on_searchQuestionerButton_cli..."
QT_MOC_LITERAL(19, 268, 32), // "on_tableWidgetItem_doubleClicked"
QT_MOC_LITERAL(20, 301, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(21, 319, 4), // "item"
QT_MOC_LITERAL(22, 324, 17), // "on_header_clicked"
QT_MOC_LITERAL(23, 342, 6) // "column"

    },
    "RanklistWidget\0requestRanklist\0\0"
    "SortMethod\0sortMethod\0requestDetailInfo\0"
    "index\0receiveRanklist\0QVector<Player>\0"
    "players\0QVector<Questioner>\0questioners\0"
    "receiveDetailInfo\0Player\0player\0"
    "Questioner\0questioner\0"
    "on_searchPlayerButton_clicked\0"
    "on_searchQuestionerButton_clicked\0"
    "on_tableWidgetItem_doubleClicked\0"
    "QTableWidgetItem*\0item\0on_header_clicked\0"
    "column"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RanklistWidget[] = {

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
       1,    1,   54,    2, 0x06 /* Public */,
       5,    2,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    3,   62,    2, 0x0a /* Public */,
      12,    2,   69,    2, 0x0a /* Public */,
      17,    0,   74,    2, 0x08 /* Private */,
      18,    0,   75,    2, 0x08 /* Private */,
      19,    1,   76,    2, 0x08 /* Private */,
      22,    1,   79,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 10, 0x80000000 | 3,    9,   11,    4,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 15,   14,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void, QMetaType::Int,   23,

       0        // eod
};

void RanklistWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RanklistWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->requestRanklist((*reinterpret_cast< SortMethod(*)>(_a[1]))); break;
        case 1: _t->requestDetailInfo((*reinterpret_cast< SortMethod(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->receiveRanklist((*reinterpret_cast< QVector<Player>(*)>(_a[1])),(*reinterpret_cast< QVector<Questioner>(*)>(_a[2])),(*reinterpret_cast< SortMethod(*)>(_a[3]))); break;
        case 3: _t->receiveDetailInfo((*reinterpret_cast< Player(*)>(_a[1])),(*reinterpret_cast< Questioner(*)>(_a[2]))); break;
        case 4: _t->on_searchPlayerButton_clicked(); break;
        case 5: _t->on_searchQuestionerButton_clicked(); break;
        case 6: _t->on_tableWidgetItem_doubleClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 7: _t->on_header_clicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RanklistWidget::*)(SortMethod );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RanklistWidget::requestRanklist)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RanklistWidget::*)(SortMethod , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RanklistWidget::requestDetailInfo)) {
                *result = 1;
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
void RanklistWidget::requestRanklist(SortMethod _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RanklistWidget::requestDetailInfo(SortMethod _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
