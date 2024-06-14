#include "saleprogress.h"
#include <QFont>
#include <QVariantMap>
#include "../../sessionmanager.h"
#include <QDebug>

extern "C"
{
#include <acs_api.h>
#include <acs_errno.h>
#include <acs_ioctl.h>
}

extern int printer_open(void);
extern int printer_setLineSpaceSM(unsigned char nr_step);

SaleProgress::SaleProgress(QWidget *parent)
    : QWidget(parent), currentIndex(0), completeTimerStarted(false), animationStarted(false)
{
    // Inicializa los iconos
    icons << QPixmap(":/assets/icons/sale/0-percent.png")
          << QPixmap(":/assets/icons/sale/20-percent.png")
          << QPixmap(":/assets/icons/sale/25-percent.png")
          << QPixmap(":/assets/icons/sale/50-percent.png")
          << QPixmap(":/assets/icons/sale/75-percent.png")
          << QPixmap(":/assets/icons/sale/80-percent.png")
          << QPixmap(":/assets/icons/sale/100-percent.png");

    // Crear un layout vertical para organizar los elementos
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0); // Eliminar márgenes
    mainLayout->setSpacing(0);                  // Ajustar el espacio entre los elementos

    // Configura el QLabel para mostrar el texto
    textLabel = new QLabel("Procesando", this);
    textLabel->setAlignment(Qt::AlignCenter);
    QFont font = textLabel->font();
    font.setPointSize(14); // Establecer el tamaño de la fuente
    font.setBold(true);    // Establecer la fuente en negrita
    textLabel->setFont(font);

    // Agrega textLabel al layout principal con un espacio alrededor
    mainLayout->addWidget(textLabel, 0, Qt::AlignCenter);
    mainLayout->addSpacing(-5); // Agrega espacio entre textLabel e iconLabel

    // Agrega iconLabel al layout principal
    iconLabel = new QLabel(this);
    mainLayout->addWidget(iconLabel, 0, Qt::AlignCenter);

    // Configura el layout principal como el diseño del widget
    setLayout(mainLayout);

    // Configura el QTimer para actualizar el icono en intervalos regulares
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateIcon()));

    // Configura el QTimer para manejar la finalización
    completeTimer = new QTimer(this);
    completeTimer->setSingleShot(true);
    connect(completeTimer, SIGNAL(timeout()), this, SLOT(handleCompleteTimer()));
}

void SaleProgress::startAnimation()
{
    if (!animationStarted)
    {
        animationStarted = true;
        timer->start(600); // Inicia la animación
    }
}

void SaleProgress::updateIcon()
{
    currentIndex = (currentIndex + 1) % icons.size();
    iconLabel->setPixmap(icons[currentIndex]);

    // Verificar si se ha alcanzado el último icono (100%)
    if (currentIndex == icons.size() - 1 && !completeTimerStarted)
    {
        completeTimerStarted = true;
        completeTimer->start(3000); // Inicializa temporizador de 3 segundos
    }
}

void SaleProgress::processJson(const QVariant &json)
{
    if (!json.isValid() || json.type() != QVariant::List)
    {
        qWarning() << "Invalid JSON format";
        return;
    }

    QVariantList list = json.toList();
    foreach (const QVariant &item, list)
    {
        QVariantMap map = item.toMap();

        QString id = map.value("id").toString();
        QString name = map.value("name").toString();
        QString description = map.value("description").toString();
        bool active = map.value("active").toBool();

        qDebug() << "ID:" << id;
        qDebug() << "Name:" << name;
        qDebug() << "Description:" << description;
        qDebug() << "Active:" << active;

        QVariantList products = map.value("products").toList();
        foreach (const QVariant &product, products)
        {
            QVariantMap productMap = product.toMap();
            QString productId = productMap.value("id").toString();
            QString productName = productMap.value("name").toString();
            QString productType = productMap.value("type").toString();
            int maxQty = productMap.value("maxQty").toInt();
            int minQty = productMap.value("minQty").toInt();
            int maxVal = productMap.value("maxVal").toInt();
            int minValue = productMap.value("minValue").toInt();
            int unitPrice = productMap.value("unitPrice").toInt();
            bool productActive = productMap.value("active").toBool();
            QString paymentMediumTypeCode = productMap.value("paymentMediumTypeCode").toString();

            qDebug() << "Product ID:" << productId;
            qDebug() << "Product Name:" << productName;
            qDebug() << "Product Type:" << productType;
            qDebug() << "Max Qty:" << maxQty;
            qDebug() << "Min Qty:" << minQty;
            qDebug() << "Max Val:" << maxVal;
            qDebug() << "Min Value:" << minValue;
            qDebug() << "Unit Price:" << unitPrice;
            qDebug() << "Product Active:" << productActive;
            qDebug() << "Payment Medium Type Code:" << paymentMediumTypeCode;
        }

        QVariantMap salesQuota = map.value("salesQuota").toMap();
        bool restricted = salesQuota.value("restricted").toBool();
        int balance = salesQuota.value("balance").toInt();
        int minBalanceAllowed = salesQuota.value("minBalanceAllowed").toInt();
        int maxBalanceAllowed = salesQuota.value("maxBalanceAllowed").toInt();

        qDebug() << "Sales Quota Restricted:" << restricted;
        qDebug() << "Sales Quota Balance:" << balance;
        qDebug() << "Sales Quota Min Balance Allowed:" << minBalanceAllowed;
        qDebug() << "Sales Quota Max Balance Allowed:" << maxBalanceAllowed;
    }
}

void SaleProgress::handleApiResponse(const QString &response)
{
    QVariant json = parseJson(response);
    processJson(json);
}

void SaleProgress::handleCompleteTimer()
{
    // Obtener valores necesarios del Singleton SessionManager
    QString posData = SessionManager::instance().getPointOfSaleData();
    QString jwtToken = SessionManager::instance().getJwtToken();
    QString userId = SessionManager::instance().getCurrentUserId();
    QString userDocument = SessionManager::instance().getCurrentUserDocument();
    int currentUnitPrice = SessionManager::instance().getCurrentUnitPrice();

    // Convertir jwtToken a un objeto JSON utilizando stringToJson
    QVariantMap jwtTokenJson = stringToJson(jwtToken);
    QString accessToken = jwtTokenJson.value("access_token").toString();

    // Verificar si existe la llave "products"
    QVariantList pointOfSaleDataList = parseJsonArray(posData);

    if (!pointOfSaleDataList.isEmpty())
    {
        // Asumimos que solo hay un objeto en la lista de pointOfSaleData
        QVariantMap pointOfSaleData = pointOfSaleDataList.first().toMap();

        if (pointOfSaleData.contains("id"))
            posId = pointOfSaleData.value("id").toString();

        // Verificar si existe la llave "products"
        if (pointOfSaleData.contains("products"))
        {
            QVariant productsVariant = pointOfSaleData.value("products");

            // Asegurarse de que el valor sea una lista
            if (productsVariant.type() == QVariant::List)
            {
                QVariantList productsList = productsVariant.toList();

                // Verificar si la lista no está vacía
                if (!productsList.isEmpty())
                {
                    QVariant productVariant = productsList.at(0);

                    // Obtener la cadena del QVariant productVariant
                    QString productString = productVariant.toString();
                    int startIndex = productString.indexOf("\"id\":\"") + 6; // Ajuste para ignorar las comillas y el texto "id":
                    int endIndex = productString.indexOf("\"", startIndex);
                    productId = productString.mid(startIndex, endIndex - startIndex);
                    qDebug() << "productId" << productId;
                }
                else
                {
                    qWarning() << "La lista de productos está vacía";
                }
            }
            else
            {
                qWarning() << "'products' no es una lista";
            }
        }
        else
        {
            qWarning() << "No se encontró la llave 'products' en pointOfSaleData";
        }
    }
    else
    {
        qWarning() << "El JSON de pointOfSaleData está vacío o no es una lista";
    }

    // Obtener la lista de productos directamente del QVariantMap
    QVariantList productList = pointOfSaleData["products"].toList();

    // Recorrer la lista de productos
    // Convierte la cadena JSON en un mapa QVariant
    QVariantMap jsonData = parseJson(posData);

    // Obtén la lista de productos

    // Crear el manager de la red
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // Conectar la señal de respuesta usando la sintaxis antigua
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(handlePostNetworkReply(QNetworkReply *)));

    // Crear la solicitud HTTP
    QNetworkRequest request;
    request.setUrl(QUrl("https://fleet.nebulae.com.co/api/external-network-gateway/rest/sale/execute"));
    request.setRawHeader("accept", "application/json"); // Especificar el tipo de contenido como JSON
    request.setRawHeader("Authorization", "Bearer " + accessToken.toUtf8());
    request.setRawHeader("Content-Type", "application/json"); // Especificar el tipo de contenido como JSON

    // Crear el cuerpo de la solicitud utilizando variables
    QString endUserId = userId;
    // productId previamente definido
    int qty = 1;
    int unitPrice = currentUnitPrice;
    QString paymentMediumId = "MIFARE-145";
    QString document = userDocument;
    QString routeCode = "";
    QString routeName = "";
    QString pointOfSaleId = posId;
    QString terminalKey = "001466";
    QString externalSystemRefId = "";
    double longitude = -75.593601;
    double latitude = 6.214901;

    QString jsonString = QString(
                             "{"
                             "\"endUserId\": \"%1\","
                             "\"ProductLines\": ["
                             "{"
                             "\"id\": \"%2\","
                             "\"qty\": %3,"
                             "\"unitPrice\": %4,"
                             "\"paymentMediumId\": \"%5\","
                             "\"metadata\": {"
                             "\"document\": \"%6\","
                             "\"routeCode\": \"%7\","
                             "\"routeName\": \"%8\""
                             "},"
                             "\"qrCode\": \"\","
                             "\"qrCodes\": [ \"\" ]"
                             "}"
                             "],"
                             "\"PaymentLines\": ["
                             "{"
                             "\"type\": \"CASH\","
                             "\"amount\": %9"
                             "}"
                             "],"
                             "\"pointOfSaleId\": \"%10\","
                             "\"terminalKey\": \"%11\","
                             "\"externalSystemRefId\": \"%12\","
                             "\"coordinates\": [ %13, %14 ]"
                             "}")
                             .arg(endUserId)
                             .arg(productId)
                             .arg(qty)
                             .arg(unitPrice)
                             .arg(paymentMediumId)
                             .arg(document)
                             .arg(routeCode)
                             .arg(routeName)
                             .arg(unitPrice)
                             .arg(pointOfSaleId)
                             .arg(terminalKey)
                             .arg(externalSystemRefId)
                             .arg(longitude)
                             .arg(latitude);

    QByteArray postData = jsonString.toUtf8();

    qDebug() << "unitPrice" << unitPrice;
    qDebug() << "endUserId" << endUserId;
    qDebug() << "productId" << productId;
    qDebug() << "qty" << qty;
    qDebug() << "unitPrice" << unitPrice;
    qDebug() << "paymentMediumId" << paymentMediumId;
    qDebug() << "document" << document;
    qDebug() << "routeName" << routeName;
    qDebug() << "pointOfSaleId" << pointOfSaleId;
    qDebug() << "currentUnitPrice" << currentUnitPrice;
    qDebug() << "terminalKey" << terminalKey;
    qDebug() << "externalSystemRefId" << externalSystemRefId;
    qDebug() << "externalSystemRefId" << externalSystemRefId;
    qDebug() << "longitude" << longitude;
    qDebug() << "latitude" << latitude;
    qDebug() << "postData" << postData;
    // Enviar la solicitud POST
    manager->post(request, postData);
}

void SaleProgress::handlePostNetworkReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray responseData = reply->readAll();
        qDebug() << "Response:" << responseData;
        emit progressDoneSuccess();
        runPrinter(responseData);
    }
    else
    {
        qDebug() << "Error en la solicitud:" << reply->errorString();
        QByteArray errorData = reply->readAll();
        qDebug() << "Detalle del error:" << errorData;
        emit progressDoneError();
    }

    // Liberar la memoria del objeto QNetworkReply
    reply->deleteLater();
}

QVariantMap SaleProgress::parseJsonObject(const QString &jsonString)
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

QVariant SaleProgress::parseJsonValue(const QString &jsonString)
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

QVariantMap SaleProgress::stringToJson(const QString &jsonString)
{
    QVariantMap jsonMap;

    // Remover los primeros y últimos caracteres, que son '{' y '}'
    QString cleanedString = jsonString.mid(1, jsonString.size() - 2);

    // Separa la cadena en pares de clave-valor utilizando el delimitador ","
    QStringList keyValuePairs = cleanedString.split(",");

    // Itera sobre los pares de clave-valor
    foreach (const QString &pair, keyValuePairs)
    {
        // Separa cada par de clave-valor utilizando el delimitador ":"
        QStringList keyValue = pair.split(":");

        // Asegúrate de que haya un par de clave-valor válido
        if (keyValue.size() == 2)
        {
            // Extrae la clave y el valor
            QString key = keyValue[0].trimmed();
            QString value = keyValue[1].trimmed();

            // Quita las comillas alrededor de la clave y el valor
            key.remove(0, 1);
            key.remove(key.size() - 1, 1);
            value.remove(0, 1);
            value.remove(value.size() - 1, 1);

            // Agrega el par de clave-valor al mapa JSON
            jsonMap[key] = value;
        }
    }

    return jsonMap;
}

QVariantList SaleProgress::parseJsonArray(const QString &jsonString)
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

QVariantMap SaleProgress::parseJson(const QString &jsonString)
{
    QVariantMap result;

    // Analiza el JSON
    QStringList jsonLines = jsonString.split("\n");
    foreach (const QString &line, jsonLines)
    {
        if (line.contains(":"))
        {
            QStringList parts = line.split(":");
            if (parts.size() == 2)
            {
                QString key = parts[0].trimmed().remove("\"");
                QString value = parts[1].trimmed().remove("\"");
                result[key] = value;
            }
        }
    }

    return result;
}

void SaleProgress::runPrinter(const QString &response)
{
    int nRet;

    nRet = printer_open();
    if (nRet < 0)
    {
        qDebug() << "ACR890_Printer_Open error" << nRet;
        return;
    }

    // Imprimir una sola vez
    PrintPage("NebulaE", "Recarga Billetera", response.toUtf8().constData(), "2024/03/19 11:42:44");

    // Cerrar la impresora
    printer_close();
}

void SaleProgress::PrintPage(const char *companyName, const char *tipoServicio, const char *sampleText, const char *dateTime)
{
    printer_setLineSpaceSM(30);
    printer_printStrSM(companyName);
    printer_printStrSM(" ");
    printer_printStrSM(sampleText);
    printer_printStrSM(" ");
    printer_printStrSM(dateTime);
    printer_printStrSM(" ");
    printer_printStrSM("acr890");
    printer_printStrSM(" ");
}
