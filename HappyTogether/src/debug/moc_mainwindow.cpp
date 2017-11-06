/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[22];
    char stringdata0[356];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 7), // "iSignal"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 1), // "b"
QT_MOC_LITERAL(4, 22, 16), // "OffActionClicked"
QT_MOC_LITERAL(5, 39, 17), // "DataActionClicked"
QT_MOC_LITERAL(6, 57, 27), // "ReceiveMessageActionClicked"
QT_MOC_LITERAL(7, 85, 24), // "SendMessageActionClicked"
QT_MOC_LITERAL(8, 110, 21), // "DocumentActionClicked"
QT_MOC_LITERAL(9, 132, 18), // "AboutActionClicked"
QT_MOC_LITERAL(10, 151, 18), // "BlackActionClicked"
QT_MOC_LITERAL(11, 170, 18), // "WhiteActionClicked"
QT_MOC_LITERAL(12, 189, 20), // "DefaultActionClicked"
QT_MOC_LITERAL(13, 210, 16), // "RunActionClicked"
QT_MOC_LITERAL(14, 227, 22), // "UpdateLogActionClicked"
QT_MOC_LITERAL(15, 250, 19), // "RecordActionClicked"
QT_MOC_LITERAL(16, 270, 16), // "SearchBtnClicked"
QT_MOC_LITERAL(17, 287, 17), // "PublishBtnClicked"
QT_MOC_LITERAL(18, 305, 14), // "JoinBtnClicked"
QT_MOC_LITERAL(19, 320, 7), // "eventID"
QT_MOC_LITERAL(20, 328, 16), // "DetailBtnClicked"
QT_MOC_LITERAL(21, 345, 10) // "JudgeEmpty"

    },
    "MainWindow\0iSignal\0\0b\0OffActionClicked\0"
    "DataActionClicked\0ReceiveMessageActionClicked\0"
    "SendMessageActionClicked\0DocumentActionClicked\0"
    "AboutActionClicked\0BlackActionClicked\0"
    "WhiteActionClicked\0DefaultActionClicked\0"
    "RunActionClicked\0UpdateLogActionClicked\0"
    "RecordActionClicked\0SearchBtnClicked\0"
    "PublishBtnClicked\0JoinBtnClicked\0"
    "eventID\0DetailBtnClicked\0JudgeEmpty"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  104,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,  107,    2, 0x08 /* Private */,
       5,    0,  108,    2, 0x08 /* Private */,
       6,    0,  109,    2, 0x08 /* Private */,
       7,    0,  110,    2, 0x08 /* Private */,
       8,    0,  111,    2, 0x08 /* Private */,
       9,    0,  112,    2, 0x08 /* Private */,
      10,    0,  113,    2, 0x08 /* Private */,
      11,    0,  114,    2, 0x08 /* Private */,
      12,    0,  115,    2, 0x08 /* Private */,
      13,    0,  116,    2, 0x08 /* Private */,
      14,    0,  117,    2, 0x08 /* Private */,
      15,    0,  118,    2, 0x08 /* Private */,
      16,    0,  119,    2, 0x08 /* Private */,
      17,    0,  120,    2, 0x08 /* Private */,
      18,    1,  121,    2, 0x08 /* Private */,
      20,    1,  124,    2, 0x08 /* Private */,
      21,    0,  127,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Bool,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->iSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->OffActionClicked(); break;
        case 2: _t->DataActionClicked(); break;
        case 3: _t->ReceiveMessageActionClicked(); break;
        case 4: _t->SendMessageActionClicked(); break;
        case 5: _t->DocumentActionClicked(); break;
        case 6: _t->AboutActionClicked(); break;
        case 7: _t->BlackActionClicked(); break;
        case 8: _t->WhiteActionClicked(); break;
        case 9: _t->DefaultActionClicked(); break;
        case 10: _t->RunActionClicked(); break;
        case 11: _t->UpdateLogActionClicked(); break;
        case 12: _t->RecordActionClicked(); break;
        case 13: _t->SearchBtnClicked(); break;
        case 14: _t->PublishBtnClicked(); break;
        case 15: _t->JoinBtnClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->DetailBtnClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: { bool _r = _t->JudgeEmpty();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::iSignal)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::iSignal(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
