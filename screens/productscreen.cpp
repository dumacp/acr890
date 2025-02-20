#include <QtGui>
#include "productscreen.h"
#include <QMessageBox>
#include <QVBoxLayout>     // Necesario para usar QVBoxLayout
#include <QListWidget>     // Necesario para usar QListWidget
#include <QListWidgetItem> // Necesario para usar QListWidget
#include "sessionmanager.h"

#include <stdio.h>

QT_BEGIN_NAMESPACE
// class QSslError;
QT_END_NAMESPACE

QT_USE_NAMESPACE

ProductScreen::ProductScreen(QWidget *parent)
    : QWidget(parent)
{
    // Crear un layout vertical para colocar los elementos de la lista
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Array de productos
    QStringList products;

    QString posDataData = SessionManager::instance().getPointOfSaleData();

    products << "RECARGA MIFARE" << "RECARGA BILLETERA" << "PRODUCTO PRUEBA";

    // Recorrer el array de productos y agregar cada uno a la lista
    for (int i = 0; i < products.size(); ++i)
    {
        // Crear un nuevo widget personalizado para el elemento de la lista
        QWidget *itemWidget = new QWidget;
        itemWidget->setObjectName("listItem"); // Asignar un nombre de objeto al widget

        // Crear un layout horizontal para el widget del elemento de la lista
        QHBoxLayout *itemLayout = new QHBoxLayout(itemWidget);

        // Agregar un QLabel para el texto del producto
        QLabel *productLabel = new QLabel(products[i]);
        productLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        productLabel->setObjectName("productLabel"); // Asignar un nombre de objeto al label del producto
        itemLayout->addWidget(productLabel);

        // Agregar un icono al elemento de lista
        QIcon icon(":/assets/icons/wallet.png");
        QLabel *iconLabel = new QLabel;
        iconLabel->setPixmap(icon.pixmap(24, 24)); // Establece el tamaño del icono según sea necesario
        itemLayout->addWidget(iconLabel);

        // Agregar el widget del elemento de lista al layout vertical
        layout->addWidget(itemWidget);

        // Crear un QPushButton para simular la interacción de clic
        QPushButton *button = new QPushButton(itemWidget);
        button->setFixedSize(itemWidget->size());
        button->setFlat(true);           // Para que el botón no tenga apariencia 3D
        button->setProperty("index", i); // Adjuntar el índice al botón como propiedad

        // Conectar la señal clicked() del botón al slot productClicked
        connect(button, SIGNAL(clicked()), this, SLOT(productClicked()));
    }

    // Establecer el layout para la ventana
    setLayout(layout);

    // Aplicar el estilo solo al elemento de la lista
    setStyleSheet(
        "#listItem { border: 1px solid black; border-radius: 4px; height: 20px; }");
}

// Slot para manejar el clic en un producto
void ProductScreen::productClicked()
{
    // Obtener el botón que emitió la señal
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button)
    {
        // Obtener el índice y el nombre del producto seleccionado
        int index = button->property("index").toInt();
        QString productName = button->parentWidget()->findChild<QLabel *>("productLabel")->text();

        // Imprimir el índice y el nombre del producto seleccionado
        qDebug() << "Producto seleccionado:" << index << "Nombre:" << productName;

        // Verificar si el nombre del producto es "RECARGA MIFARE" antes de emitir la señal
        if (productName == "RECARGA MIFARE")
        {
            emit selectedProductMifare();
        }

        // Verificar si el nombre del producto es "RECARGA BILLETERA" antes de emitir la señal
        if (productName == "RECARGA BILLETERA")
        {
            emit selectedProduct();
        }
    }
}

// Data parser
QVariantMap ProductScreen::parseJsonObject(const QString &jsonString)
{
    QVariantMap jsonMap;
    QRegExp rx("\"([^\"]*)\"\\s*:\\s*([^,\\{\\}\\[\\]]+|\\{[^\\}]*\\}|\\[[^\\]]*\\])");
    int pos = 0;

    while ((pos = rx.indexIn(jsonString, pos)) != -1)
    {
        QString key = rx.cap(1);
        QString value = rx.cap(2);

        jsonMap[key] = parseJsonValue(value);

        pos += rx.matchedLength();
    }

    return jsonMap;
}

QVariant ProductScreen::parseJsonValue(const QString &jsonString)
{
    if (jsonString.startsWith('{'))
    {
        return parseJsonObject(jsonString);
    }
    else if (jsonString.startsWith('['))
    {
        return parseJsonArray(jsonString);
    }
    else if (jsonString == "true")
    {
        return true;
    }
    else if (jsonString == "false")
    {
        return false;
    }
    else if (jsonString == "null")
    {
        return QVariant();
    }
    else if (jsonString.startsWith('"'))
    {
        return jsonString.mid(1, jsonString.length() - 2); // Remove quotes
    }
    else
    {
        bool ok;
        int intValue = jsonString.toInt(&ok);
        if (ok)
        {
            return intValue;
        }
        double doubleValue = jsonString.toDouble(&ok);
        if (ok)
        {
            return doubleValue;
        }
    }
    return jsonString; // As fallback
}

QVariantList ProductScreen::parseJsonArray(const QString &jsonString)
{
    QVariantList jsonArray;
    QRegExp rx("([^,\\[\\]\\{\\}]+|\\{[^\\}]*\\}|\\[[^\\]]*\\])");
    int pos = 1; // Skip the initial '['

    while ((pos = rx.indexIn(jsonString, pos)) != -1)
    {
        QString value = rx.cap(1);
        jsonArray.append(parseJsonValue(value));

        pos += rx.matchedLength();
    }

    return jsonArray;
}
