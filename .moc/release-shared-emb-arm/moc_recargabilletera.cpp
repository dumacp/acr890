/****************************************************************************
** Meta object code from reading C++ file 'recargabilletera.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../screens/recargabilletera.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'recargabilletera.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RecargaBilleteraScreen[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x05,

 // slots: signature, parameters, type, tag, flags
      41,   23,   23,   23, 0x0a,
      56,   23,   23,   23, 0x0a,
      83,   23,   23,   23, 0x0a,
     116,  110,   23,   23, 0x0a,
     151,   23,   23,   23, 0x0a,
     192,  181,  172,   23, 0x0a,
     229,  181,  216,   23, 0x0a,
     270,  253,   23,   23, 0x0a,
     300,   23,   23,   23, 0x0a,
     336,  324,  320,   23, 0x0a,
     378,  373,   23,   23, 0x0a,
     415,  373,  407,   23, 0x0a,
     444,   23,   23,   23, 0x0a,
     474,   23,   23,   23, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RecargaBilleteraScreen[] = {
    "RecargaBilleteraScreen\0\0showSaleScreen()\0"
    "handleSubmit()\0handleTextChanged(QString)\0"
    "getCurrentBalance(QString)\0reply\0"
    "handleNetworkReply(QNetworkReply*)\0"
    "executeSale(QString)\0QVariant\0jsonString\0"
    "parseJsonValue(QString)\0QVariantList\0"
    "parseJsonArray(QString)\0balance,response\0"
    "updateSaldoLabel(int,QString)\0"
    "restoreSaldoLabel()\0int\0priceString\0"
    "removeCommasAndConvertToInt(QString)\0"
    "text\0validateAddressText(QString)\0"
    "QString\0extractNumericValue(QString)\0"
    "emitSaleSuccessToMainWindow()\0"
    "emitSaleErrorToMainWindow()\0"
};

void RecargaBilleteraScreen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RecargaBilleteraScreen *_t = static_cast<RecargaBilleteraScreen *>(_o);
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
        case 11: _t->validateAddressText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: { QString _r = _t->extractNumericValue((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 13: _t->emitSaleSuccessToMainWindow(); break;
        case 14: _t->emitSaleErrorToMainWindow(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RecargaBilleteraScreen::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RecargaBilleteraScreen::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RecargaBilleteraScreen,
      qt_meta_data_RecargaBilleteraScreen, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RecargaBilleteraScreen::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RecargaBilleteraScreen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RecargaBilleteraScreen::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RecargaBilleteraScreen))
        return static_cast<void*>(const_cast< RecargaBilleteraScreen*>(this));
    return QWidget::qt_metacast(_clname);
}

int RecargaBilleteraScreen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void RecargaBilleteraScreen::showSaleScreen()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
