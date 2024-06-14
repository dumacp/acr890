/****************************************************************************
** Meta object code from reading C++ file 'dialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../screens/dialog/dialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ResponseDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,
      31,   15,   15,   15, 0x05,
      44,   15,   15,   15, 0x05,
      63,   15,   15,   15, 0x05,
      77,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      89,   15,   15,   15, 0x08,
     116,   15,   15,   15, 0x08,
     141,   15,   15,   15, 0x08,
     165,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ResponseDialog[] = {
    "ResponseDialog\0\0loginSuccess()\0"
    "loginError()\0loginServerError()\0"
    "saleSuccess()\0saleError()\0"
    "emitLoginSuccessAndClose()\0"
    "emitLoginErrorAndClose()\0"
    "emitSaleErrorAndClose()\0"
    "emitSaleSuccessAndClose()\0"
};

void ResponseDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ResponseDialog *_t = static_cast<ResponseDialog *>(_o);
        switch (_id) {
        case 0: _t->loginSuccess(); break;
        case 1: _t->loginError(); break;
        case 2: _t->loginServerError(); break;
        case 3: _t->saleSuccess(); break;
        case 4: _t->saleError(); break;
        case 5: _t->emitLoginSuccessAndClose(); break;
        case 6: _t->emitLoginErrorAndClose(); break;
        case 7: _t->emitSaleErrorAndClose(); break;
        case 8: _t->emitSaleSuccessAndClose(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ResponseDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ResponseDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ResponseDialog,
      qt_meta_data_ResponseDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ResponseDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ResponseDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ResponseDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ResponseDialog))
        return static_cast<void*>(const_cast< ResponseDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ResponseDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void ResponseDialog::loginSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ResponseDialog::loginError()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ResponseDialog::loginServerError()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void ResponseDialog::saleSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void ResponseDialog::saleError()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
