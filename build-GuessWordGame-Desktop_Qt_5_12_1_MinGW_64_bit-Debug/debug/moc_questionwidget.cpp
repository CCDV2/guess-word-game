/****************************************************************************
** Meta object code from reading C++ file 'questionwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GuessWordGame/questionwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'questionwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QuestionWidget_t {
    QByteArrayData data[15];
    char stringdata0[196];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QuestionWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QuestionWidget_t qt_meta_stringdata_QuestionWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "QuestionWidget"
QT_MOC_LITERAL(1, 15, 20), // "sendQuestionWordList"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 13), // "QVector<Word>"
QT_MOC_LITERAL(4, 51, 5), // "words"
QT_MOC_LITERAL(5, 57, 14), // "questionerName"
QT_MOC_LITERAL(6, 72, 21), // "requireQuestionerName"
QT_MOC_LITERAL(7, 94, 17), // "receiveAddedWords"
QT_MOC_LITERAL(8, 112, 5), // "count"
QT_MOC_LITERAL(9, 118, 9), // "expGained"
QT_MOC_LITERAL(10, 128, 21), // "receiveQuestionerName"
QT_MOC_LITERAL(11, 150, 15), // "_questionerName"
QT_MOC_LITERAL(12, 166, 10), // "paintEvent"
QT_MOC_LITERAL(13, 177, 12), // "QPaintEvent*"
QT_MOC_LITERAL(14, 190, 5) // "event"

    },
    "QuestionWidget\0sendQuestionWordList\0"
    "\0QVector<Word>\0words\0questionerName\0"
    "requireQuestionerName\0receiveAddedWords\0"
    "count\0expGained\0receiveQuestionerName\0"
    "_questionerName\0paintEvent\0QPaintEvent*\0"
    "event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QuestionWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       6,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    2,   45,    2, 0x0a /* Public */,
      10,    1,   50,    2, 0x0a /* Public */,
      12,    1,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    4,    5,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, 0x80000000 | 13,   14,

       0        // eod
};

void QuestionWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QuestionWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendQuestionWordList((*reinterpret_cast< QVector<Word>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->requireQuestionerName(); break;
        case 2: _t->receiveAddedWords((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->receiveQuestionerName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->paintEvent((*reinterpret_cast< QPaintEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QuestionWidget::*)(QVector<Word> , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QuestionWidget::sendQuestionWordList)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QuestionWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QuestionWidget::requireQuestionerName)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QuestionWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_QuestionWidget.data,
    qt_meta_data_QuestionWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QuestionWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QuestionWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QuestionWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int QuestionWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void QuestionWidget::sendQuestionWordList(QVector<Word> _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QuestionWidget::requireQuestionerName()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
