#include "mifaresaleprogress.h"
#include <QFont>
#include <QVariantMap>
#include <QDebug>

#include <QtGui>
#include <QMessageBox>
#include <QVariantMap>
#include <QVariantList>
#include <QByteArray>
#include <QTextStream>
#include <QRegExp>

// Session Manager - Singleton
#include "../../sessionmanager.h"
#include <cstddef>

// Custom Transmit
AcsReader _cReaderMifareSaleScreen;

extern "C"
{
#include <acs_api.h>
#include <acs_errno.h>
#include <acs_ioctl.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
}

extern int printer_open(void);
extern int printer_setLineSpaceSM(unsigned char nr_step);

MifareSaleProgress::MifareSaleProgress(QWidget *parent)
    : QWidget(parent), currentIndex(0), completeTimerStarted(false), animationStarted(false), startWriting(false)
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
    connect(completeTimer, SIGNAL(timeout()), this, SLOT(handleCompleteTimer()));
}

MifareSaleProgress::~MifareSaleProgress()
{
    cardData.clear();
    cardDataSecond.clear();
    atrNumberConfig.clear();
    uuidConfig.clear();
    stepNumber.clear();
    sessionIdConfig.clear();
    responseApdus.clear();
    endUserDocument.clear();

    currentIndex = 0;
    completeTimerStarted = false;
    timer->stop();
    completeTimer->stop();
    animationStarted = false;

    startWriting = false;

    jwtToken.clear();
    posId.clear();
    userName.clear();
    userId.clear();
    userDocument.clear();
    currentBalance.clear();
    modifyingText.clear();

    pointOfSaleDataString.clear();
    pointOfSaleData.clear();
    posId.clear();
    posData.clear();
    productId.clear();
    jwtToken.clear();
    userId.clear();
    userDocument.clear();
    currentUnitPrice.clear();

    payId.clear();
    endUserFullname.clear();
    endUserId.clear();
    message.clear();

    additionalTextLabel->clear();

    additionalIconLabel->clear();
}

void MifareSaleProgress::startAnimation()
{
    if (!animationStarted)
    {
        animationStarted = true;
        timer->start(300); // Inicia la animación
    }
}

void MifareSaleProgress::updateIcon()
{
    currentIndex = (currentIndex + 1) % icons.size();
    iconLabel->setPixmap(icons[currentIndex]);

    // Verificar si se ha alcanzado el último icono (100%)
    if (currentIndex == icons.size() - 1 && !completeTimerStarted)
    {
        completeTimerStarted = true;
        completeTimer->start(500); // Inicializa temporizador de 3 segundos
    }
}

void MifareSaleProgress::processJson(const QVariant &json)
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

void MifareSaleProgress::handleApiResponse(const QString &response)
{
    QVariant json = parseJson(response);
    processJson(json);
}

void MifareSaleProgress::handleCompleteTimer()
{

    currentIndex = 0;
    completeTimerStarted = false;
    timer->stop();
    completeTimer->stop();
    animationStarted = false;

    QString posData = SessionManager::instance().getPointOfSaleData();
    // Obtener el accessToken actual
    QString jwtToken = SessionManager::instance().getJwtToken();
    QVariantMap jwtTokenJson = stringToJson(jwtToken);
    QString accessToken = jwtTokenJson.value("access_token").toString();

    // Verificar si existe la llave "products"
    QVariantList pointOfSaleDataList = parseJsonArray(posData);

    if (!pointOfSaleDataList.isEmpty())
    {
        QVariantMap pointOfSaleData = pointOfSaleDataList.first().toMap();

        if (pointOfSaleData.contains("id"))
        {
            posId = pointOfSaleData.value("id").toString();
        }
    }

    QString pointOfSaleId = posId;
    QString productId = "013624e8-75b9-4ea6-b35a-3d69af074548";

    // Obtener la lista de productos directamente del QVariantMap
    QVariantList productList = pointOfSaleData["products"].toList();

    // Recorrer la lista de productos
    // Convierte la cadena JSON en un mapa QVariant
    QVariantMap jsonData = parseJson(posData);

    // Crear el manager de la red
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // Conectar la señal de respuesta usando la sintaxis antigua
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(handlePostNetworkReplySale(QNetworkReply *)));

    // Crear la solicitud HTTP
    QNetworkRequest request;
    request.setUrl(QUrl("https://fleet.nebulae.com.co/api/external-network-gateway/rest/sale/execute"));
    request.setRawHeader("accept", "application/json"); // Especificar el tipo de contenido como JSON
    request.setRawHeader("Authorization", "Bearer " + accessToken.toUtf8());
    request.setRawHeader("Content-Type", "application/json"); // Especificar el tipo de contenido como JSON

    // Crear el cuerpo de la solicitud utilizando variables

    int qty = 1;
    int unitPrice = SessionManager::instance().getCurrentMifareUnitPrice();
    QString paymentMediumId = SessionManager::instance().getPaymentMediumId();
    QString terminalKey = "001466";
    QString externalSystemRefId = "";
    double longitude = -75.593601;
    double latitude = 6.214901;

    QString jsonString = QString(
                             "{"
                             "\"ProductLines\": ["
                             "{"
                             "\"id\": \"%1\","
                             "\"qty\": %2,"
                             "\"unitPrice\": %3,"
                             "\"paymentMediumId\": \"%4\""
                             "}"
                             "],"
                             "\"PaymentLines\": ["
                             "{"
                             "\"type\": \"CASH\","
                             "\"amount\": %5"
                             "}"
                             "],"
                             "\"pointOfSaleId\": \"%6\","
                             "\"terminalKey\": \"%7\","
                             "\"externalSystemRefId\": \"%8\","
                             "\"coordinates\": [ %9, %10 ]"
                             "}")
                             .arg(productId)
                             .arg(qty)
                             .arg(unitPrice)
                             .arg(paymentMediumId)
                             .arg(unitPrice)
                             .arg(pointOfSaleId)
                             .arg(terminalKey)
                             .arg(externalSystemRefId)
                             .arg(longitude)
                             .arg(latitude);

    QByteArray postData = jsonString.toUtf8();

    qDebug() << "unitPrice" << unitPrice;
    qDebug() << "qty" << qty;
    qDebug() << "unitPrice" << unitPrice;
    qDebug() << "paymentMediumId" << paymentMediumId;
    qDebug() << "pointOfSaleId" << pointOfSaleId;
    qDebug() << "currentUnitPrice" << currentUnitPrice;
    qDebug() << "terminalKey" << terminalKey;
    qDebug() << "externalSystemRefId" << externalSystemRefId;
    qDebug() << "externalSystemRefId" << externalSystemRefId;
    qDebug() << "longitude" << longitude;
    qDebug() << "latitude" << latitude;
    qDebug() << "posData" << postData;

    // Enviar la solicitud POST
    manager->post(request, postData);
}

void MifareSaleProgress::handlePostNetworkReplySale(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray responseData = reply->readAll();
        qDebug() << "Response:" << responseData;
        piccReader();
    }
    else
    {
        qDebug() << "Error en la solicitud:" << reply->errorString();
        QByteArray errorData = reply->readAll();
        qDebug() << "Detalle del error:" << errorData;
        emit progressMifareDoneError();
    }

    // Liberar la memoria del objeto QNetworkReply
    reply->deleteLater();
}

QVariantMap MifareSaleProgress::parseJsonObject(const QString &jsonString)
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

QVariant MifareSaleProgress::parseJsonValue(const QString &jsonString)
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

QVariantMap MifareSaleProgress::stringToJson(const QString &jsonString)
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

QVariantList MifareSaleProgress::parseJsonArray(const QString &jsonString)
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

QVariantMap MifareSaleProgress::parseJson(const QString &jsonString)
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

void MifareSaleProgress::runPrinter(const QString &response)
{
    int nRet;

    nRet = printer_open();
    if (nRet < 0)
    {
        qDebug() << "ACR890_Printer_Open error" << nRet;
        return;
    }

    // Imprimir una sola vez
    PrintPage("NebulaE", "Recarga Mifare", response.toUtf8().constData(), "2024/03/19 11:42:44");

    // Cerrar la impresora
    printer_close();
}

void MifareSaleProgress::PrintPage(const char *companyName, const char *tipoServicio, const char *sampleText, const char *dateTime)
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

// Card
void MifareSaleProgress::piccReader()
{

    int picc_rtn;
    int rtn;
    int i;
    char uid_buf[10];
    unsigned char atr[64];
    unsigned char atr_len;

    struct picc_card picc_card_info;
    char picc_uid_str[64];

    picc_rtn = picc_open();
    if (picc_rtn == 0)
    {
        qDebug() << "picc_open successful!";
    }
    else
    {
        qDebug() << "picc_open failed!";
        emit progressMifareDoneError();
        return;
    }

    memset(atr, 0, sizeof(atr));
    rtn = picc_power_on(atr, &atr_len);
    if (rtn == 0)
    {
        // Crear un stringstream para construir la cadena ATR Y UUID
        std::stringstream atrValue;
        std::stringstream uuidValue;

        printf("ATR = ");
        for (i = 0; i < atr_len; i++)
        {
            printf("0x%02x ", atr[i]);
            atrValue << std::hex << std::setw(2) << std::setfill('0') << (int)atr[i]; // Almacenar cada elemento del array atr[] como un unico string - Así obtenemos el ATR
        }
        printf("\n");

        memset(picc_uid_str, 0, sizeof(picc_uid_str));
        rtn = picc_poll_card(&picc_card_info);
        printf("UID = ");
        for (i = 0; i < picc_card_info.uidlength; i++)
        {
            printf("0x%02x ", picc_card_info.uid[i]);                                                 // Almacenar cada elemento del array picc_card_info.uid[] como un unico string - Así obtenemos el UID
            uuidValue << std::hex << std::setw(2) << std::setfill('0') << (int)picc_card_info.uid[i]; // Almacenar cada elemento del array picc_card_info.uid[] como un unico string - Así obtenemos el UUID
            sprintf(uid_buf, "0x%02x ", picc_card_info.uid[i]);
            strcat(picc_uid_str, uid_buf);
        }
        printf("\n");

        // Almacenar el atrValue y uuidValue
        std::string atrStd = atrValue.str();
        std::string uuidStd = uuidValue.str();

        atrNumberConfig = QString::fromUtf8(atrStd.c_str(), atrStd.length());
        uuidConfig = QString::fromUtf8(uuidStd.c_str(), uuidStd.length());

        // Ejecutar lectura-escritura FLEET
        readWriteCard(atrNumberConfig, uuidConfig.toUpper());
    }
    else
    {
        qDebug() << "picc_power_on failed!";
        emit progressMifareDoneError();
        picc_close();
    }
}

void MifareSaleProgress::readWriteCard(const QString &atr, const QString &uuid)
{

    currentIndex = 0;
    completeTimerStarted = false;
    timer->stop();
    completeTimer->stop();
    animationStarted = false;

    textLabel->setText("Aplicando Cambios");

    /*  animationStarted = true;
     timer->start(300); // Inicia la animación */

    // Crear el manager de la red
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // Obtener el accessToken actual
    QString jwtToken = SessionManager::instance().getJwtToken();
    QVariantMap jwtTokenJson = stringToJson(jwtToken);
    QString accessToken = jwtTokenJson.value("access_token").toString();

    // Crear la solicitud HTTP
    QNetworkRequest request;
    request.setUrl(QUrl("https://fleet.nebulae.com.co/api/external-network-gateway/rest/paymentMedium/applyPendingMods"));
    request.setRawHeader("accept", "application/json"); // Especificar el tipo de contenido como JSON
    request.setRawHeader("Authorization", "Bearer " + accessToken.toUtf8());
    request.setRawHeader("Content-Type", "application/json"); // Especificar el tipo de contenido como JSON

    // Crear el cuerpo de la solicitud utilizando variables
    QString atrPos = atr;   // ATR
    QString uuidPos = uuid; // UUID

    QString posData = SessionManager::instance().getPointOfSaleData();
    QVariantList pointOfSaleDataList = parseJsonArray(posData);

    if (!pointOfSaleDataList.isEmpty())
    {
        QVariantMap pointOfSaleData = pointOfSaleDataList.first().toMap();

        if (pointOfSaleData.contains("id"))
        {
            posId = pointOfSaleData.value("id").toString();
        }
    }

    QString pointOfSaleId = posId;

    QString terminalKey = "001466";

    QString jsonString = QString(
                             "{"
                             "\"atr\": \"%1\","
                             "\"uuid\": \"%2\","
                             "\"metadata\": {"
                             "\"pointOfSaleId\": \"%3\","
                             "\"terminalKey\": \"%4\""
                             "}"
                             "}")
                             .arg(atrPos)
                             .arg(uuidPos)
                             .arg(pointOfSaleId)
                             .arg(terminalKey);

    QByteArray postData = jsonString.toUtf8();

    qDebug() << "atr" << atrPos;
    qDebug() << "uuid" << uuidPos;
    qDebug() << "pointOfSaleId" << pointOfSaleId;
    qDebug() << "terminalKey" << terminalKey;
    qDebug() << "accessToken" << accessToken;

    // Conectar la señal de respuesta usando la sintaxis antigua
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(handlePostNetworkReply(QNetworkReply *)));

    // Enviar la solicitud POST
    manager->post(request, postData);
}

void MifareSaleProgress::handlePostNetworkReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray responseData = reply->readAll();
        qDebug() << "Primera respuesta:" << responseData;
        cardData = QString(responseData);
        QVariantMap cardDataMap = parseJsonObject(cardData);
        if (cardDataMap.contains("nextStep"))
        {
            QVariantMap nextStep = cardDataMap["nextStep"].toMap();
            if (nextStep.contains("step"))
                QString stepNumber = nextStep["step"].toString();
            if (nextStep.contains("desc"))
            {
                QString description = nextStep["desc"].toString();
                qDebug() << "Descripción: " << description;
            }
            if (nextStep.contains("sessionId"))
            {
                QString sessionId = nextStep["sessionId"].toString();
                sessionIdConfig = sessionId;
            }

            if (nextStep.contains("requestApdus"))
            {
                QVariantList requestApdus = nextStep["requestApdus"].toList();
                std::vector<ParsedApduResponse> responseApdus; // Array to push every APDU response
                foreach (QVariant var, requestApdus)
                {
                    QString requestApdu = var.toString();

                    QByteArray commandTransform = requestApdu.toLatin1();
                    char *command = commandTransform.data();

                    uint8_t commandLength = static_cast<uint8_t>(sizeof(command));

                    char response[256];
                    ulong responseLength = 0;
                    CARD_READER cardReaderType = READER_PICC;

                    int status = _cReaderMifareSaleScreen.customTransmit(cardReaderType, command, commandLength, response, &responseLength);

                    if (status != 0)
                    {
                        qDebug() << "Error en la transmisión:" << status;
                        picc_close();
                        emit progressMifareDoneError();
                        return;
                    }

                    ApduResponse apduResponse;

                    // Validar si la tarjeta es Mifare Plus
                    bool mplus;
                    if (atrNumberConfig.size() < 13 * 2)
                    {
                        mplus = true;
                        apduResponse = _cReaderMifareSaleScreen.parseResponsePlus(response, responseLength, mplus);
                    }

                    // Validar si la tarjeta es Mifare Classic
                    bool mclassic;
                    if (atrNumberConfig.size() >= 13 * 2)
                    {
                        mclassic = true;
                        apduResponse = _cReaderMifareSaleScreen.parseResponseClassic(response, responseLength, mclassic);
                    }

                    ParsedApduResponse parsedResponse = _cReaderMifareSaleScreen.convertToParsedApduResponse(apduResponse, requestApdu);

                    responseApdus.push_back(parsedResponse);

                    qDebug() << "apdu:" << parsedResponse.requestApdu;
                    qDebug() << "isValid:" << parsedResponse.isValid;
                    qDebug() << "response:" << parsedResponse.responseApdu;
                }
                // Enviar array con APDUs de respuesta
                QString atrStepZero = atrNumberConfig;
                QString uuidStepZero = uuidConfig;
                readWriteCardStepZero(responseApdus);
            }
        }
    }
    else
    {
        qDebug() << "Error en la solicitud:" << reply->errorString();
        QByteArray errorData = reply->readAll();
        qDebug() << "Detalle del error:" << errorData;

        // Cerrar lectora
        picc_close();

        // Manejar Error
        emit progressMifareDoneError();
    }
    // Liberar la memoria del objeto QNetworkReply
    reply->deleteLater();
}

void MifareSaleProgress::readWriteCardStepZero(std::vector<ParsedApduResponse> responseApdus)
{
    // Crear el manager de la red
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // Obtener el accessToken actual
    QString jwtToken = SessionManager::instance().getJwtToken();
    QVariantMap jwtTokenJson = stringToJson(jwtToken);
    QString accessToken = jwtTokenJson.value("access_token").toString();

    // Crear la solicitud HTTP
    QNetworkRequest request;
    request.setUrl(QUrl("https://fleet.nebulae.com.co/api/external-network-gateway/rest/paymentMedium/applyPendingMods"));
    request.setRawHeader("accept", "application/json"); // Especificar el tipo de contenido como JSON
    request.setRawHeader("Authorization", "Bearer " + accessToken.toUtf8());
    request.setRawHeader("Content-Type", "application/json"); // Especificar el tipo de contenido como JSON

    // Crear el cuerpo de la solicitud utilizando variables
    QString atrPos = atrNumberConfig; // ATR
    QString uuidPos = uuidConfig.toUpper();

    QString posData = SessionManager::instance().getPointOfSaleData();

    // Verificar si existe la llave "products"
    QVariantList pointOfSaleDataList = parseJsonArray(posData);

    if (!pointOfSaleDataList.isEmpty())
    {
        QVariantMap pointOfSaleData = pointOfSaleDataList.first().toMap();

        if (pointOfSaleData.contains("id"))
        {
            posId = pointOfSaleData.value("id").toString();
        }
    }

    QString pointOfSaleId = posId;
    QString terminalKey = "001466";
    QString posSessionId = sessionIdConfig;
    qDebug() << "size respondeApdu" << responseApdus.size();
    QString responseApdusJson = generarResponseApdus(responseApdus);

    QString jsonString = QString(
                             "{"
                             "\"atr\": \"%1\",\n"
                             "\"uuid\": \"%2\",\n"
                             "\"metadata\": {\n"
                             "  \"pointOfSaleId\": \"%3\",\n"
                             "  \"terminalKey\": \"%4\"\n"
                             "},\n"
                             "\"sessionId\": \"%5\",\n"
                             "\"responseApdus\": [%6]\n"
                             "}\n")
                             .arg(atrPos)
                             .arg(uuidPos)
                             .arg(pointOfSaleId)
                             .arg(terminalKey)
                             .arg(posSessionId)
                             .arg(responseApdusJson); // Llama a una función que genera el contenido de "responseApdus"

    QByteArray postData = jsonString.toUtf8();

    qDebug() << "jsonString Final" << jsonString;

    // Conectar la señal de respuesta usando la sintaxis antigua
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(handlePostNetworkReplyZero(QNetworkReply *)));

    // Enviar la solicitud POST
    manager->post(request, postData);
}

void MifareSaleProgress::handlePostNetworkReplyZero(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray responseData = reply->readAll();
        qDebug() << "Respuesta:" << responseData;

        cardDataSecond = QString(responseData);
        QVariantMap cardDataMap = parseJsonObject(cardDataSecond);

        if (cardDataMap.contains("nextStep"))
        {
            QVariantMap nextStep = cardDataMap["nextStep"].toMap();
            QVariantMap paymentMedium = cardDataMap["paymentMedium"].toMap();
            if (nextStep.size() > 0)
            {
                if (nextStep.contains("step"))
                {
                    QString step = nextStep["step"].toString();
                    if (step.isNull())
                    {
                        QString error = nextStep["error"].toString();
                        qDebug() << "error" << error;

                        // Cerrar lectora
                        picc_close();

                        // Manejar Error
                        emit progressMifareDoneError();
                    }
                }
                if (nextStep.contains("desc"))
                {
                    QString description = nextStep["desc"].toString();
                    qDebug() << "Descripción: " << description;
                }
                if (nextStep.contains("sessionId"))
                {
                    QString sessionId = nextStep["sessionId"].toString();
                    sessionIdConfig = sessionId;
                }
                if (nextStep.contains("requestApdus"))
                {
                    QVariantList requestApdus = nextStep["requestApdus"].toList();
                    std::vector<ParsedApduResponse> responseApdus; // Array to push every APDU response
                    foreach (QVariant var, requestApdus)
                    {
                        QString requestApdu = var.toString();

                        QByteArray commandTransform = requestApdu.toLatin1();
                        char *command = commandTransform.data();

                        uint8_t commandLength = static_cast<uint8_t>(sizeof(command));

                        char response[256];
                        ulong responseLength = 0;
                        CARD_READER cardReaderType = READER_PICC;

                        int status = _cReaderMifareSaleScreen.customTransmit(cardReaderType, command, commandLength, response, &responseLength);

                        if (status != 0)
                        {
                            qDebug() << "Error en la transmisión:" << status;

                            // Cerrar lectora
                            picc_close();

                            // Manejar Error
                            emit progressMifareDoneError();
                            return;
                        }

                        ApduResponse apduResponse;

                        // Validar si la tarjeta es Mifare Plus
                        bool mplus;
                        if (atrNumberConfig.size() < 13 * 2)
                        {
                            mplus = true;
                            apduResponse = _cReaderMifareSaleScreen.parseResponsePlus(response, responseLength, mplus);
                        }

                        // Validar si la tarjeta es Mifare Classic
                        bool mclassic;
                        if (atrNumberConfig.size() >= 13 * 2)
                        {
                            mclassic = true;
                            apduResponse = _cReaderMifareSaleScreen.parseResponseClassic(response, responseLength, mclassic);
                        }

                        ParsedApduResponse parsedResponse = _cReaderMifareSaleScreen.convertToParsedApduResponse(apduResponse, requestApdu);

                        responseApdus.push_back(parsedResponse);

                        qDebug() << "apdu:" << parsedResponse.requestApdu;
                        qDebug() << "isValid:" << parsedResponse.isValid;
                        qDebug() << "response:" << parsedResponse.responseApdu;
                    }
                    // Enviar array con APDUs de respuesta
                    QString atrStepZero = atrNumberConfig;
                    QString uuidStepZero = uuidConfig;
                    readWriteCardStepZero(responseApdus);
                }
            }
            else
            {
                qDebug() << "Lectura finalizada";

                if (paymentMedium.size() > 0)
                {
                    if (paymentMedium.contains("id"))
                    {
                        payId = paymentMedium.value("id").toString();
                    }
                    endUserFullname = paymentMedium["endUserFullName"].toString();
                    endUserDocument = paymentMedium["endUserDocument"].toString();
                    endUserId = paymentMedium["endUserId"].toString();

                    if (paymentMedium.contains("pockets"))
                    {
                        QVariantMap pockets = paymentMedium["pockets"].toMap();

                        if (pockets.contains("REGULAR"))
                        {
                            QVariantMap regularPocket = pockets["REGULAR"].toMap();
                            QString pocketType = regularPocket["type"].toString();
                            balance = regularPocket["balance"].toInt();
                            int balanceBk = regularPocket["balanceBk"].toInt();
                            qint64 timestamp = regularPocket["timestamp"].toLongLong();
                            qDebug() << "Saldo Actualizado: " << balance;
                        }

                        if (pockets.contains("FINANCIAL_ENTITY"))
                        {
                            QVariantMap financialEntityPocket = pockets["FINANCIAL_ENTITY"].toMap();
                            QString financialType = financialEntityPocket["type"].toString();
                            int financialBalance = financialEntityPocket["balance"].toInt();
                            int financialBalanceBk = financialEntityPocket["balanceBk"].toInt();
                            qint64 financialTimestamp = financialEntityPocket["timestamp"].toLongLong();
                        }
                    }

                    qDebug() << "endUserFullname:" << endUserFullname;
                    qDebug() << "endUserDocument: " << endUserDocument;
                    qDebug() << "endUserId: " << endUserId;

                    message = QString("Saldo Actualizado: %1\n"
                                      "endUserFullname: %2\n"
                                      "endUserDocument: %3\n"
                                      "endUserId: %4")
                                  .arg(balance)
                                  .arg(endUserFullname)
                                  .arg(endUserDocument)
                                  .arg(endUserId);
                    SessionManager::instance().setMessageToPrint(message);
                }

                picc_close();
                runPrinter(message);
                emit progressMifareDoneSuccess();
            }
        }
    }
    else
    {
        qDebug() << "Error en la solicitud:" << reply->errorString();
        QByteArray errorData = reply->readAll();
        qDebug() << "Detalle del error:" << errorData;

        // Cerrar lectora
        picc_close();

        // Manejgar error
        emit progressMifareDoneError();
    }
    // Liberar la memoria del objeto QNetworkReply
    reply->deleteLater();
}

// Función para generar el contenido de "responseApdus"
QString MifareSaleProgress::generarResponseApdus(const std::vector<ParsedApduResponse> responseApdus)
{
    QStringList responseItems;

    for (size_t i = 0; i < responseApdus.size(); i++)
    {

        // Construir el string para cada ParsedApduResponse
        QString responseItem = QString("{ \"requestApdu\": \"%1\", \"isValid\": %2, \"responseApdu\": \"%3\" }")
                                   .arg(responseApdus[i].requestApdu)
                                   .arg(responseApdus[i].isValid ? "true" : "false")
                                   .arg(responseApdus[i].responseApdu);

        // Agregar el item a la lista
        responseItems << responseItem;
    }

    // Unir todos los elementos en un solo string separado por comas
    QString resultString = responseItems.join(",\n");

    return resultString;
}