/****************************************************************************
** Meta object code from reading C++ file 'mifaresaleprogress.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../screens/sale/animation/mifaresaleprogress.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mifaresaleprogress.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MifareSaleProgress[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,
      48,   19,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
      74,   19,   19,   19, 0x08,
      87,   19,   19,   19, 0x08,
     115,  109,   19,   19, 0x08,
     163,  158,   19,   19, 0x08,
     194,  185,   19,   19, 0x08,
     241,  230,  221,   19, 0x08,
     278,  230,  265,   19, 0x08,
     314,  230,  302,   19, 0x08,
     336,  230,  302,   19, 0x08,
     361,  230,  302,   19, 0x08,
     380,   19,   19,   19, 0x08,
     402,  393,   19,   19, 0x08,
     433,  109,   19,   19, 0x08,
     486,  472,   19,   19, 0x08,
     541,  109,   19,   19, 0x08,
     584,  185,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MifareSaleProgress[] = {
    "MifareSaleProgress\0\0progressMifareDoneSuccess()\0"
    "progressMifareDoneError()\0updateIcon()\0"
    "handleCompleteTimer()\0reply\0"
    "handlePostNetworkReplySale(QNetworkReply*)\0"
    "json\0processJson(QVariant)\0response\0"
    "handleApiResponse(QString)\0QVariant\0"
    "jsonString\0parseJsonValue(QString)\0"
    "QVariantList\0parseJsonArray(QString)\0"
    "QVariantMap\0stringToJson(QString)\0"
    "parseJsonObject(QString)\0parseJson(QString)\0"
    "piccReader()\0atr,uuid\0"
    "readWriteCard(QString,QString)\0"
    "handlePostNetworkReply(QNetworkReply*)\0"
    "responseApdus\0"
    "readWriteCardStepZero(std::vector<ParsedApduResponse>)\0"
    "handlePostNetworkReplyZero(QNetworkReply*)\0"
    "runPrinter(QString)\0"
};

void MifareSaleProgress::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MifareSaleProgress *_t = static_cast<MifareSaleProgress *>(_o);
        switch (_id) {
        case 0: _t->progressMifareDoneSuccess(); break;
        case 1: _t->progressMifareDoneError(); break;
        case 2: _t->updateIcon(); break;
        case 3: _t->handleCompleteTimer(); break;
        case 4: _t->handlePostNetworkReplySale((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 5: _t->processJson((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 6: _t->handleApiResponse((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: { QVariant _r = _t->parseJsonValue((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 8: { QVariantList _r = _t->parseJsonArray((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = _r; }  break;
        case 9: { QVariantMap _r = _t->stringToJson((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = _r; }  break;
        case 10: { QVariantMap _r = _t->parseJsonObject((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = _r; }  break;
        case 11: { QVariantMap _r = _t->parseJson((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = _r; }  break;
        case 12: _t->piccReader(); break;
        case 13: _t->readWriteCard((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 14: _t->handlePostNetworkReply((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 15: _t->readWriteCardStepZero((*reinterpret_cast< std::vector<ParsedApduResponse>(*)>(_a[1]))); break;
        case 16: _t->handlePostNetworkReplyZero((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 17: _t->runPrinter((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MifareSaleProgress::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MifareSaleProgress::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MifareSaleProgress,
      qt_meta_data_MifareSaleProgress, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MifareSaleProgress::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MifareSaleProgress::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MifareSaleProgress::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MifareSaleProgress))
        return static_cast<void*>(const_cast< MifareSaleProgress*>(this));
    return QWidget::qt_metacast(_clname);
}

int MifareSaleProgress::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void MifareSaleProgress::progressMifareDoneSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MifareSaleProgress::progressMifareDoneError()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
