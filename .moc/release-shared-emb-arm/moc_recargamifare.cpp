/****************************************************************************
** Meta object code from reading C++ file 'recargamifare.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../screens/recargamifare.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'recargamifare.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RecargaMifareScreen[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
      44,   20,   20,   20, 0x0a,
      59,   20,   20,   20, 0x0a,
      86,   20,   20,   20, 0x0a,
     127,  116,  107,   20, 0x0a,
     168,  151,   20,   20, 0x0a,
     198,   20,   20,   20, 0x0a,
     234,  222,  218,   20, 0x0a,
     276,  271,   20,   20, 0x0a,
     313,  271,  305,   20, 0x0a,
     342,   20,   20,   20, 0x0a,
     378,   20,   20,   20, 0x0a,
     412,   20,   20,   20, 0x0a,
     425,   20,   20,   20, 0x0a,
     449,  440,   20,   20, 0x0a,
     486,  480,   20,   20, 0x0a,
     539,  525,   20,   20, 0x0a,
     594,  480,   20,   20, 0x0a,
     649,  116,  637,   20, 0x0a,
     687,  116,  674,   20, 0x0a,
     711,  525,  305,   20, 0x0a,
     765,  116,  637,   20, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RecargaMifareScreen[] = {
    "RecargaMifareScreen\0\0showMifareSaleScreen()\0"
    "handleSubmit()\0handleTextChanged(QString)\0"
    "executeSale(QString)\0QVariant\0jsonString\0"
    "parseJsonValue(QString)\0balance,response\0"
    "updateSaldoLabel(int,QString)\0"
    "restoreSaldoLabel()\0int\0priceString\0"
    "removeCommasAndConvertToInt(QString)\0"
    "text\0validateAddressText(QString)\0"
    "QString\0extractNumericValue(QString)\0"
    "emitMifareSaleSuccessToMainWindow()\0"
    "emitMifareSaleErrorToMainWindow()\0"
    "piccReader()\0checkForCard()\0atr,uuid\0"
    "readWriteCard(QString,QString)\0reply\0"
    "handlePostNetworkReply(QNetworkReply*)\0"
    "responseApdus\0"
    "readWriteCardStepZero(std::vector<ParsedApduResponse>)\0"
    "handlePostNetworkReplyZero(QNetworkReply*)\0"
    "QVariantMap\0parseJsonObject(QString)\0"
    "QVariantList\0parseJsonArray(QString)\0"
    "generarResponseApdus(std::vector<ParsedApduResponse>)\0"
    "stringToJson(QString)\0"
};

void RecargaMifareScreen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RecargaMifareScreen *_t = static_cast<RecargaMifareScreen *>(_o);
        switch (_id) {
        case 0: _t->showMifareSaleScreen(); break;
        case 1: _t->handleSubmit(); break;
        case 2: _t->handleTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->executeSale((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: { QVariant _r = _t->parseJsonValue((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 5: _t->updateSaldoLabel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: _t->restoreSaldoLabel(); break;
        case 7: { int _r = _t->removeCommasAndConvertToInt((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 8: _t->validateAddressText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: { QString _r = _t->extractNumericValue((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 10: _t->emitMifareSaleSuccessToMainWindow(); break;
        case 11: _t->emitMifareSaleErrorToMainWindow(); break;
        case 12: _t->piccReader(); break;
        case 13: _t->checkForCard(); break;
        case 14: _t->readWriteCard((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 15: _t->handlePostNetworkReply((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 16: _t->readWriteCardStepZero((*reinterpret_cast< std::vector<ParsedApduResponse>(*)>(_a[1]))); break;
        case 17: _t->handlePostNetworkReplyZero((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 18: { QVariantMap _r = _t->parseJsonObject((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = _r; }  break;
        case 19: { QVariantList _r = _t->parseJsonArray((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = _r; }  break;
        case 20: { QString _r = _t->generarResponseApdus((*reinterpret_cast< const std::vector<ParsedApduResponse>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 21: { QVariantMap _r = _t->stringToJson((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RecargaMifareScreen::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RecargaMifareScreen::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RecargaMifareScreen,
      qt_meta_data_RecargaMifareScreen, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RecargaMifareScreen::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RecargaMifareScreen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RecargaMifareScreen::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RecargaMifareScreen))
        return static_cast<void*>(const_cast< RecargaMifareScreen*>(this));
    return QWidget::qt_metacast(_clname);
}

int RecargaMifareScreen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void RecargaMifareScreen::showMifareSaleScreen()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
