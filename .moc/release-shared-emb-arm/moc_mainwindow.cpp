/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      30,   11,   11,   11, 0x08,
      47,   11,   11,   11, 0x08,
      67,   11,   11,   11, 0x08,
      96,   11,   11,   11, 0x08,
     122,   11,   11,   11, 0x08,
     150,   11,   11,   11, 0x08,
     184,   11,   11,   11, 0x08,
     210,   11,   11,   11, 0x08,
     242,   11,   11,   11, 0x08,
     273,   11,   11,   11, 0x08,
     301,   11,   11,   11, 0x08,
     321,   11,   11,   11, 0x08,
     340,   11,   11,   11, 0x08,
     359,   11,   11,   11, 0x08,
     380,   11,   11,   11, 0x08,
     407,   11,   11,   11, 0x08,
     429,   11,   11,   11, 0x08,
     442,   11,   11,   11, 0x08,
     463,  457,   11,   11, 0x08,
     519,  508,  496,   11, 0x08,
     541,   11,   11,   11, 0x08,
     562,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0showLoginScreen()\0"
    "showHomeScreen()\0showProductScreen()\0"
    "showRecargaBilleteraScreen()\0"
    "showRecargaMifareScreen()\0"
    "changeToSaleSuccessScreen()\0"
    "changeToMifareSaleSuccessScreen()\0"
    "changeToSaleErrorScreen()\0"
    "changeToMifareSaleErrorScreen()\0"
    "changeBackToRecargaBilletera()\0"
    "changeBackToRecargaMifare()\0"
    "showHistoryScreen()\0showConfigScreen()\0"
    "setAuthenticated()\0changeToSaleScreen()\0"
    "changeToMifareSaleScreen()\0"
    "setNotAuthenticated()\0updateTime()\0"
    "refreshToken()\0reply\0"
    "handleTokenReply(QNetworkReply*)\0"
    "QVariantMap\0jsonString\0stringToJson(QString)\0"
    "changeToWifiScreen()\0changeToWifiConnectScreen()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->showLoginScreen(); break;
        case 1: _t->showHomeScreen(); break;
        case 2: _t->showProductScreen(); break;
        case 3: _t->showRecargaBilleteraScreen(); break;
        case 4: _t->showRecargaMifareScreen(); break;
        case 5: _t->changeToSaleSuccessScreen(); break;
        case 6: _t->changeToMifareSaleSuccessScreen(); break;
        case 7: _t->changeToSaleErrorScreen(); break;
        case 8: _t->changeToMifareSaleErrorScreen(); break;
        case 9: _t->changeBackToRecargaBilletera(); break;
        case 10: _t->changeBackToRecargaMifare(); break;
        case 11: _t->showHistoryScreen(); break;
        case 12: _t->showConfigScreen(); break;
        case 13: _t->setAuthenticated(); break;
        case 14: _t->changeToSaleScreen(); break;
        case 15: _t->changeToMifareSaleScreen(); break;
        case 16: _t->setNotAuthenticated(); break;
        case 17: _t->updateTime(); break;
        case 18: _t->refreshToken(); break;
        case 19: _t->handleTokenReply((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 20: { QVariantMap _r = _t->stringToJson((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = _r; }  break;
        case 21: _t->changeToWifiScreen(); break;
        case 22: _t->changeToWifiConnectScreen(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
