/****************************************************************************
** Meta object code from reading C++ file 'wifisetup.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../screens/wifisetup.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wifisetup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WifiScreen[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      45,   34,   11,   11, 0x08,
      78,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_WifiScreen[] = {
    "WifiScreen\0\0changeToWifiConnect()\0"
    "row,column\0handleCellDoubleClicked(int,int)\0"
    "scanResults()\0"
};

void WifiScreen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WifiScreen *_t = static_cast<WifiScreen *>(_o);
        switch (_id) {
        case 0: _t->changeToWifiConnect(); break;
        case 1: _t->handleCellDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->scanResults(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WifiScreen::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WifiScreen::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WifiScreen,
      qt_meta_data_WifiScreen, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WifiScreen::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WifiScreen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WifiScreen::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WifiScreen))
        return static_cast<void*>(const_cast< WifiScreen*>(this));
    return QWidget::qt_metacast(_clname);
}

int WifiScreen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void WifiScreen::changeToWifiConnect()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
