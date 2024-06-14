#ifndef PRODUCTSCREEN_H
#define PRODUCTSCREEN_H

#include <QWidget>
#include <QList>
#include <QListWidgetItem>

/* #include <QtNetwork/QSslError> // Mover la inclusión aquí */

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QTextEdit;
QT_END_NAMESPACE

//! [class definition]
class ProductScreen : public QWidget
{
    Q_OBJECT

public:
    ProductScreen(QWidget *parent = 0);
    void rotateWindow();

signals:
    void itemClicked(QListWidgetItem *item);
    void selectedProduct();

public slots:
    void productClicked();
};
//! [class definition]

#endif
