/****************************************************************************
** Meta object code from reading C++ file 'configscreen.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../screens/configscreen.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'configscreen.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ConfigScreen[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,   13,   13,   13, 0x0a,
      43,   13,   13,   13, 0x0a,
      56,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ConfigScreen[] = {
    "ConfigScreen\0\0changeToWifiSetup()\0"
    "runLed()\0turnOffLed()\0goToWifiSettings()\0"
};

void ConfigScreen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ConfigScreen *_t = static_cast<ConfigScreen *>(_o);
        switch (_id) {
        case 0: _t->changeToWifiSetup(); break;
        case 1: _t->runLed(); break;
        case 2: _t->turnOffLed(); break;
        case 3: _t->goToWifiSettings(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ConfigScreen::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ConfigScreen::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ConfigScreen,
      qt_meta_data_ConfigScreen, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ConfigScreen::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ConfigScreen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ConfigScreen::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ConfigScreen))
        return static_cast<void*>(const_cast< ConfigScreen*>(this));
    return QWidget::qt_metacast(_clname);
}

int ConfigScreen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ConfigScreen::changeToWifiSetup()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
