/****************************************************************************
** Meta object code from reading C++ file 'mifaresalesuccess.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../screens/sale/success/mifaresalesuccess.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mifaresalesuccess.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MifareSaleSuccess[] = {

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
      19,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      40,   18,   18,   18, 0x08,
      65,   18,   18,   18, 0x08,
     123,   78,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MifareSaleSuccess[] = {
    "MifareSaleSuccess\0\0backToMifareScreen()\0"
    "backToMifareScreenSlot()\0runPrinter()\0"
    "companyName,tipoServicio,sampleText,dateTime\0"
    "PrintPage(const char*,const char*,const char*,const char*)\0"
};

void MifareSaleSuccess::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MifareSaleSuccess *_t = static_cast<MifareSaleSuccess *>(_o);
        switch (_id) {
        case 0: _t->backToMifareScreen(); break;
        case 1: _t->backToMifareScreenSlot(); break;
        case 2: _t->runPrinter(); break;
        case 3: _t->PrintPage((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< const char*(*)>(_a[2])),(*reinterpret_cast< const char*(*)>(_a[3])),(*reinterpret_cast< const char*(*)>(_a[4]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MifareSaleSuccess::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MifareSaleSuccess::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MifareSaleSuccess,
      qt_meta_data_MifareSaleSuccess, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MifareSaleSuccess::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MifareSaleSuccess::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MifareSaleSuccess::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MifareSaleSuccess))
        return static_cast<void*>(const_cast< MifareSaleSuccess*>(this));
    return QWidget::qt_metacast(_clname);
}

int MifareSaleSuccess::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void MifareSaleSuccess::backToMifareScreen()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
