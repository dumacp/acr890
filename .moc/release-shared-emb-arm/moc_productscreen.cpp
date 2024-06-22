/****************************************************************************
** Meta object code from reading C++ file 'productscreen.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../screens/productscreen.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'productscreen.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ProductScreen[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   15,   14,   14, 0x05,
      50,   14,   14,   14, 0x05,
      68,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      92,   14,   14,   14, 0x0a,
     132,  121,  109,   14, 0x0a,
     166,  121,  157,   14, 0x0a,
     203,  121,  190,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ProductScreen[] = {
    "ProductScreen\0\0item\0itemClicked(QListWidgetItem*)\0"
    "selectedProduct()\0selectedProductMifare()\0"
    "productClicked()\0QVariantMap\0jsonString\0"
    "parseJsonObject(QString)\0QVariant\0"
    "parseJsonValue(QString)\0QVariantList\0"
    "parseJsonArray(QString)\0"
};

void ProductScreen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ProductScreen *_t = static_cast<ProductScreen *>(_o);
        switch (_id) {
        case 0: _t->itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->selectedProduct(); break;
        case 2: _t->selectedProductMifare(); break;
        case 3: _t->productClicked(); break;
        case 4: { QVariantMap _r = _t->parseJsonObject((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = _r; }  break;
        case 5: { QVariant _r = _t->parseJsonValue((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 6: { QVariantList _r = _t->parseJsonArray((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantList*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ProductScreen::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ProductScreen::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ProductScreen,
      qt_meta_data_ProductScreen, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ProductScreen::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ProductScreen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ProductScreen::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ProductScreen))
        return static_cast<void*>(const_cast< ProductScreen*>(this));
    return QWidget::qt_metacast(_clname);
}

int ProductScreen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ProductScreen::itemClicked(QListWidgetItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ProductScreen::selectedProduct()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ProductScreen::selectedProductMifare()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
