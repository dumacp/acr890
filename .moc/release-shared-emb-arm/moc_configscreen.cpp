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
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      23,   13,   13,   13, 0x0a,
      36,   13,   13,   13, 0x0a,
      55,   49,   13,   13, 0x0a,
     103,   94,   13,   13, 0x0a,
     154,  143,  134,   13, 0x0a,
     190,  143,  178,   13, 0x0a,
     228,  143,  215,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ConfigScreen[] = {
    "ConfigScreen\0\0runLed()\0turnOffLed()\0"
    "piccReader()\0reply\0"
    "handlePostNetworkReply(QNetworkReply*)\0"
    "atr,uuid\0readWriteCard(QString,QString)\0"
    "QVariant\0jsonString\0parseJsonValue(QString)\0"
    "QVariantMap\0parseJsonObject(QString)\0"
    "QVariantList\0parseJsonArray(QString)\0"
};

void ConfigScreen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ConfigScreen *_t = static_cast<ConfigScreen *>(_o);
        switch (_id) {
        case 0: _t->runLed(); break;
        case 1: _t->turnOffLed(); break;
        case 2: _t->piccReader(); break;
        case 3: _t->handlePostNetworkReply((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 4: _t->readWriteCard((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: { QVariant _r = _t->parseJsonValue((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: { QVariantMap _r = _t->parseJsonObject((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = _r; }  break;
        case 7: { QVariantList _r = _t->parseJsonArray((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
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
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
