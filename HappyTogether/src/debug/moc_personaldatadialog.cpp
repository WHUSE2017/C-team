/****************************************************************************
** Meta object code from reading C++ file 'personaldatadialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../personaldatadialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'personaldatadialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PersonalDataDialog_t {
    QByteArrayData data[9];
    char stringdata0[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PersonalDataDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PersonalDataDialog_t qt_meta_stringdata_PersonalDataDialog = {
    {
QT_MOC_LITERAL(0, 0, 18), // "PersonalDataDialog"
QT_MOC_LITERAL(1, 19, 17), // "ConfirmBtnClicked"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 16), // "ChangeBtnClicked"
QT_MOC_LITERAL(4, 55, 9), // "OpenImage"
QT_MOC_LITERAL(5, 65, 10), // "JudgeEmpty"
QT_MOC_LITERAL(6, 76, 13), // "isNotDigitStr"
QT_MOC_LITERAL(7, 90, 3), // "src"
QT_MOC_LITERAL(8, 94, 10) // "isDigitStr"

    },
    "PersonalDataDialog\0ConfirmBtnClicked\0"
    "\0ChangeBtnClicked\0OpenImage\0JudgeEmpty\0"
    "isNotDigitStr\0src\0isDigitStr"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PersonalDataDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    1,   48,    2, 0x08 /* Private */,
       8,    1,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QString,    7,
    QMetaType::Bool, QMetaType::QString,    7,

       0        // eod
};

void PersonalDataDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PersonalDataDialog *_t = static_cast<PersonalDataDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ConfirmBtnClicked(); break;
        case 1: _t->ChangeBtnClicked(); break;
        case 2: _t->OpenImage(); break;
        case 3: { bool _r = _t->JudgeEmpty();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->isNotDigitStr((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { bool _r = _t->isDigitStr((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject PersonalDataDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_PersonalDataDialog.data,
      qt_meta_data_PersonalDataDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PersonalDataDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PersonalDataDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PersonalDataDialog.stringdata0))
        return static_cast<void*>(const_cast< PersonalDataDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int PersonalDataDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
