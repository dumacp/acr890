/****************************************************************************
** Meta object code from reading C++ file 'saleprogress.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../screens/sale/animation/saleprogress.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'saleprogress.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SaleProgress[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      36,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      56,   13,   13,   13, 0x08,
      69,   13,   13,   13, 0x08,
      97,   91,   13,   13, 0x08,
     141,  136,   13,   13, 0x08,
     172,  163,   13,   13, 0x08,
     219,  208,  199,   13, 0x08,
     256,  208,  243,   13, 0x08,
     280,  163,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SaleProgress[] = {
    "SaleProgress\0\0progressDoneSuccess()\0"
    "progressDoneError()\0updateIcon()\0"
    "handleCompleteTimer()\0reply\0"
    "handlePostNetworkReply(QNetworkReply*)\0"
    "json\0processJson(QVariant)\0response\0"
    "handleApiResponse(QString)\0QVariant\0"
    "jsonString\0parseJsonValue(QString)\0"
    "QVariantList\0parseJsonArray(QString)\0"
    "runPrinter(QString)\0"
};

void SaleProgress::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SaleProgress *_t = static_cast<SaleProgress *>(_o);
        switch (_id) {
        case 0: _t->progressDoneSuccess(); break;
        case 1: _t->progressDoneError(); break;
        case 2: _t->updateIcon(); break;
        case 3: _t->handleCompleteTimer(); break;
        case 4: _t->handlePostNetworkReply((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 5: _t->processJson((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 6: _t->handleApiResponse((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: { QVariant _r = _t->parseJsonValue((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 8: { QVariantList _r = _t->parseJsonArray((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = _r; }  break;
        case 9: _t->runPrinter((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SaleProgress::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SaleProgress::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SaleProgress,
      qt_meta_data_SaleProgress, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SaleProgress::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SaleProgress::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SaleProgress::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SaleProgress))
        return static_cast<void*>(const_cast< SaleProgress*>(this));
    return QWidget::qt_metacast(_clname);
}

int SaleProgress::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void SaleProgress::progressDoneSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void SaleProgress::progressDoneError()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
