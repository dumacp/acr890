/****************************************************************************
** Meta object code from reading C++ file 'loginscreen.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../screens/loginscreen.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'loginscreen.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LoginScreen[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      31,   12,   12,   12, 0x05,
      47,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      60,   12,   12,   12, 0x0a,
      75,   12,   12,   12, 0x0a,
     102,   12,   12,   12, 0x0a,
     129,  123,   12,   12, 0x0a,
     173,   12,   12,   12, 0x0a,
     204,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LoginScreen[] = {
    "LoginScreen\0\0loginSuccessful()\0"
    "submitClicked()\0authFailed()\0"
    "handleSubmit()\0handleTextChanged(QString)\0"
    "handleNetworkReply()\0reply\0"
    "handleSecondaryNetworkReply(QNetworkReply*)\0"
    "emitLoginSuccessToMainWindow()\0"
    "emitLoginErrorToMainWindow()\0"
};

void LoginScreen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LoginScreen *_t = static_cast<LoginScreen *>(_o);
        switch (_id) {
        case 0: _t->loginSuccessful(); break;
        case 1: _t->submitClicked(); break;
        case 2: _t->authFailed(); break;
        case 3: _t->handleSubmit(); break;
        case 4: _t->handleTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->handleNetworkReply(); break;
        case 6: _t->handleSecondaryNetworkReply((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 7: _t->emitLoginSuccessToMainWindow(); break;
        case 8: _t->emitLoginErrorToMainWindow(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LoginScreen::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LoginScreen::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LoginScreen,
      qt_meta_data_LoginScreen, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LoginScreen::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LoginScreen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LoginScreen::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoginScreen))
        return static_cast<void*>(const_cast< LoginScreen*>(this));
    return QWidget::qt_metacast(_clname);
}

int LoginScreen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void LoginScreen::loginSuccessful()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void LoginScreen::submitClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void LoginScreen::authFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
