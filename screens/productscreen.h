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
    void selectedProductMifare();

public slots:
    void productClicked();
    QVariantMap parseJsonObject(const QString &jsonString);
    QVariant parseJsonValue(const QString &jsonString);
    QVariantList parseJsonArray(const QString &jsonString);

private:
    /*  QString posData; */
};
//! [class definition]

#endif
