/****************************************************************************
** Meta object code from reading C++ file 'wificonnect.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../screens/wificonnect.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wificonnect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WifiConnectScreen[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      36,   18,   18,   18, 0x0a,
      51,   18,   18,   18, 0x0a,
      78,   18,   18,   18, 0x0a,
     111,  105,   18,   18, 0x0a,
     146,   18,   18,   18, 0x0a,
     187,  176,  167,   18, 0x0a,
     224,  176,  211,   18, 0x0a,
     265,  248,   18,   18, 0x0a,
     295,   18,   18,   18, 0x0a,
     331,  319,  315,   18, 0x0a,
     381,  376,  368,   18, 0x0a,
     410,   18,   18,   18, 0x0a,
     440,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WifiConnectScreen[] = {
    "WifiConnectScreen\0\0showSaleScreen()\0"
    "handleSubmit()\0handleTextChanged(QString)\0"
    "getCurrentBalance(QString)\0reply\0"
    "handleNetworkReply(QNetworkReply*)\0"
    "executeSale(QString)\0QVariant\0jsonString\0"
    "parseJsonValue(QString)\0QVariantList\0"
    "parseJsonArray(QString)\0balance,response\0"
    "updateSaldoLabel(int,QString)\0"
    "restoreSaldoLabel()\0int\0priceString\0"
    "removeCommasAndConvertToInt(QString)\0"
    "QString\0text\0extractNumericValue(QString)\0"
    "emitSaleSuccessToMainWindow()\0"
    "emitSaleErrorToMainWindow()\0"
};

void WifiConnectScreen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WifiConnectScreen *_t = static_cast<WifiConnectScreen *>(_o);
        switch (_id) {
        case 0: _t->showSaleScreen(); break;
        case 1: _t->handleSubmit(); break;
        case 2: _t->handleTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->getCurrentBalance((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->handleNetworkReply((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 5: _t->executeSale((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: { QVariant _r = _t->parseJsonValue((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 7: { QVariantList _r = _t->parseJsonArray((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = _r; }  break;
        case 8: _t->updateSaldoLabel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 9: _t->restoreSaldoLabel(); break;
        case 10: { int _r = _t->removeCommasAndConvertToInt((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 11: { QString _r = _t->extractNumericValue((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 12: _t->emitSaleSuccessToMainWindow(); break;
        case 13: _t->emitSaleErrorToMainWindow(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WifiConnectScreen::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WifiConnectScreen::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WifiConnectScreen,
      qt_meta_data_WifiConnectScreen, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WifiConnectScreen::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WifiConnectScreen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WifiConnectScreen::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WifiConnectScreen))
        return static_cast<void*>(const_cast< WifiConnectScreen*>(this));
    return QWidget::qt_metacast(_clname);
}

int WifiConnectScreen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void WifiConnectScreen::showSaleScreen()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
