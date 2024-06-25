#include <QtGui>
#include "configscreen.h"
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QFile>
#include <QFileInfo>
#include <QNetworkRequest>
#include <QStringList>
#include <QTimer>
#include <QUrl>
#include <stdio.h>

#include <QVariantMap>
#include <QVariantList>
#include <QByteArray>
#include <QTextStream>
#include <QRegExp>

// #include <smartCard/AcsIncludes.h>

// Session Manager - Singleton
#include "sessionmanager.h"
#include <cstddef>

// String build
#include <iostream>
#include <sstream>
#include <iomanip>

// Custom Transmit
AcsReader _cReaderConfigScreen;

#include <QtCore/QVector>
#include <QtCore/QList>

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

ConfigScreen::ConfigScreen(QWidget *parent)
    : QWidget(parent)
{
    // Inicializar QSignalMappper
    signalMapper = new QSignalMapper(this);

    // Conectar la señal del QSignalMapper al slot
    connect(signalMapper, SIGNAL(mapped(QObject *)), this, SLOT(handleMappedReply(QObject *)));

    // Descripción panel de configuración
    QLabel *paragraphLabel = new QLabel("Lorem Ipsum is simply dummy text of the printing and typesetting industry.");
    paragraphLabel->setFont(QFont("Arial", 11)); // Ajusta el tamaño de la fuente según sea necesario
    paragraphLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    paragraphLabel->setWordWrap(true);                  // Permitir el ajuste de línea automático si el texto es demasiado largo
    paragraphLabel->setMaximumWidth(this->width() / 2); // Limitar el ancho al 50% del ancho de la ventana

    // Notificaciones
    QPushButton *notificationsButton = new QPushButton();
    QIcon notificationsIcon(":/assets/icons/config/interface-essential-alarm-bell-off.png");
    notificationsButton->setIcon(notificationsIcon);
    notificationsButton->setIconSize(QSize(32, 32)); // Establece el tamaño del icono según sea necesario
    notificationsButton->setStyleSheet("border: 2px solid black; background-color: white;");
    notificationsButton->setStyleSheet("border: none");

    // Usuario
    QPushButton *userConfigButton = new QPushButton();
    QIcon userConfigIcon(":/assets/icons/config/multiple-user.png");
    userConfigButton->setIcon(userConfigIcon);
    userConfigButton->setIconSize(QSize(32, 32)); // Establece el tamaño del icono según sea necesario
    userConfigButton->setStyleSheet("border: 2px solid black; background-color: white;");
    userConfigButton->setStyleSheet("border: none");

    // Red Movil
    QPushButton *mobileNetConfigButton = new QPushButton();
    QIcon mobileNetConfigIcon(":/assets/icons/config/phone-signal-full.png");
    mobileNetConfigButton->setIcon(mobileNetConfigIcon);
    mobileNetConfigButton->setIconSize(QSize(32, 32)); // Establece el tamaño del icono según sea necesario
    mobileNetConfigButton->setStyleSheet("border: 2px solid black; background-color: white;");
    mobileNetConfigButton->setStyleSheet("border: none");

    // Calendar
    QPushButton *calendarConfigButton = new QPushButton();
    QIcon calendarConfigIcon(":/assets/icons/config/interface-essential-calendar-date.png");
    calendarConfigButton->setIcon(calendarConfigIcon);
    calendarConfigButton->setIconSize(QSize(32, 32)); // Establece el tamaño del icono según sea necesario
    calendarConfigButton->setStyleSheet("border: 2px solid black; background-color: white;");
    calendarConfigButton->setStyleSheet("border: none");

    // Files
    QPushButton *filesConfigButton = new QPushButton();
    QIcon filesConfigIcon(":/assets/icons/config/content-files-archive-books-1.png");
    filesConfigButton->setIcon(filesConfigIcon);
    filesConfigButton->setIconSize(QSize(32, 32)); // Establece el tamaño del icono según sea necesario
    filesConfigButton->setStyleSheet("border: 2px solid black; background-color: white;");
    filesConfigButton->setStyleSheet("border: none");

    // Docs
    QPushButton *docsConfigButton = new QPushButton();
    QIcon docsConfigIcon(":/assets/icons/config/interface-essential-clip-1.png");
    docsConfigButton->setIcon(docsConfigIcon);
    docsConfigButton->setIconSize(QSize(32, 32)); // Establece el tamaño del icono según sea necesario
    docsConfigButton->setStyleSheet("border: 2px solid black; background-color: white;");
    docsConfigButton->setStyleSheet("border: none");

    // Language
    QPushButton *langConfigButton = new QPushButton();
    QIcon langConfigIcon(":/assets/icons/config/interface-essential-translate.png");
    langConfigButton->setIcon(langConfigIcon);
    langConfigButton->setIconSize(QSize(32, 32)); // Establece el tamaño del icono según sea necesario
    langConfigButton->setStyleSheet("border: 2px solid black; background-color: white;");
    langConfigButton->setStyleSheet("border: none");

    // Wifi
    QPushButton *wifiConfButton = new QPushButton();
    QIcon wifiConfIcon(":/assets/icons/config/interface-essential-wifi-feed.png");
    wifiConfButton->setIcon(wifiConfIcon);
    wifiConfButton->setIconSize(QSize(32, 32)); // Establece el tamaño del icono según sea necesario
    wifiConfButton->setStyleSheet("border: 2px solid black; background-color: white;");
    wifiConfButton->setStyleSheet("border: none");

    // Money
    QPushButton *moneyConfButton = new QPushButton();
    QIcon moneyConfIcon(":/assets/icons/config/business-money-coin-currency.png");
    moneyConfButton->setIcon(moneyConfIcon);
    moneyConfButton->setIconSize(QSize(32, 32)); // Establece el tamaño del icono según sea necesario
    moneyConfButton->setStyleSheet("border: 2px solid black; background-color: white;");
    moneyConfButton->setStyleSheet("border: none");

    // Security
    QPushButton *securityConfButton = new QPushButton();
    QIcon securityConfIcon(":/assets/icons/config/coding-apps-websites-shield-lock.png");
    securityConfButton->setIcon(securityConfIcon);
    securityConfButton->setIconSize(QSize(32, 32)); // Establece el tamaño del icono según sea necesario
    securityConfButton->setStyleSheet("border: 2px solid black; background-color: white;");
    securityConfButton->setStyleSheet("border: none");

    // Trash
    QPushButton *trashConfButton = new QPushButton();
    QIcon trashConfIcon(":/assets/icons/config/interface-essential-bin.png");
    trashConfButton->setIcon(trashConfIcon);
    trashConfButton->setIconSize(QSize(32, 32)); // Establece el tamaño del icono según sea necesario
    trashConfButton->setStyleSheet("border: 2px solid black; background-color: white;");
    trashConfButton->setStyleSheet("border: none");

    // Info
    QPushButton *infoConfButton = new QPushButton();
    QIcon infoConfIcon(":/assets/icons/config/interface-essential-information-circle-1.png");
    infoConfButton->setIcon(infoConfIcon);
    infoConfButton->setIconSize(QSize(32, 32)); // Establece el tamaño del icono según sea necesario
    infoConfButton->setStyleSheet("border: 2px solid black; background-color: white;");
    infoConfButton->setStyleSheet("border: none");

    // Layout principal
    QGridLayout *mainLayout = new QGridLayout;

    // Agregar elementos al layout
    mainLayout->addWidget(paragraphLabel, 0, 0, 1, 4, Qt::AlignLeft); // Párrafo alineado a la izquierda horizontalmente en todas las columnas

    mainLayout->addWidget(notificationsButton, 2, 0, 1, 1, Qt::AlignCenter);   // Botón centrado debajo de los inputs
    mainLayout->addWidget(userConfigButton, 2, 1, 1, 1, Qt::AlignCenter);      // Botón centrado debajo de los inputs
    mainLayout->addWidget(mobileNetConfigButton, 2, 2, 1, 1, Qt::AlignCenter); // Botón centrado debajo de los inputs
    mainLayout->addWidget(calendarConfigButton, 2, 3, 1, 1, Qt::AlignCenter);  // Widget personalizado

    mainLayout->addWidget(filesConfigButton, 3, 0, 1, 1, Qt::AlignCenter); // Botón centrado debajo de los inputs
    mainLayout->addWidget(docsConfigButton, 3, 1, 1, 1, Qt::AlignCenter);  // Botón centrado debajo de los inputs
    mainLayout->addWidget(langConfigButton, 3, 2, 1, 1, Qt::AlignCenter);  // Botón centrado debajo de los inputs
    mainLayout->addWidget(wifiConfButton, 3, 3, 1, 1, Qt::AlignCenter);    // Widget personalizado

    mainLayout->addWidget(moneyConfButton, 4, 0, 1, 1, Qt::AlignCenter);    // Botón centrado debajo de los inputs
    mainLayout->addWidget(securityConfButton, 4, 1, 1, 1, Qt::AlignCenter); // Botón centrado debajo de los inputs
    mainLayout->addWidget(trashConfButton, 4, 2, 1, 1, Qt::AlignCenter);    // Botón centrado debajo de los inputs
    mainLayout->addWidget(infoConfButton, 4, 3, 1, 1, Qt::AlignCenter);     // Widget personalizado

    setLayout(mainLayout);

    // Fullscreen
    setWindowState(windowState() ^ Qt::WindowFullScreen);

    connect(infoConfButton, SIGNAL(clicked()), this, SLOT(runLed()));
    connect(moneyConfButton, SIGNAL(clicked()), this, SLOT(piccReader()));
}

void ConfigScreen::runLed()
{
    struct led_state state;

    // Activar las luces LED
    for (int i = 0; i < 4; ++i)
    {
        state.OnOffBlinkState = (enum led_blink_state)2;
        state.OnTimeMs = 1000;
        state.OffTimeMs = 60;
        led_set_state((enum led_id)i, state);
    }

    // Configurar un QTimer para apagar el LED después de un segundo
    QTimer::singleShot(1000, this, SLOT(turnOffLed()));
}

void ConfigScreen::turnOffLed()
{
    struct led_state state;

    // Apagar las luces LED
    for (int i = 0; i < 4; ++i)
    {
        state.OnOffBlinkState = (enum led_blink_state)0;
        led_set_state((enum led_id)i, state);
    }
}

void ConfigScreen::printResponseApdus(const std::vector<ParsedApduResponse> &responseApdus)
{
    for (std::vector<ParsedApduResponse>::const_iterator it = responseApdus.begin(); it != responseApdus.end(); ++it)
    {
        qDebug() << "APDU:" << it->requestApdu;
        qDebug() << "IsValid:" << it->isValid;
        qDebug() << "Response:" << it->responseApdu;
    }
}

void ConfigScreen::readWriteCard(const QString &atr, const QString &uuid)
{
    // Crear el manager de la red
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // Obtener el accessToken actual
    QString accessToken = SessionManager::instance().getCurrentAccessToken();

    // Crear la solicitud HTTP
    QNetworkRequest request;
    request.setUrl(QUrl("https://fleet.nebulae.com.co/api/external-network-gateway/rest/paymentMedium/applyPendingMods"));
    request.setRawHeader("accept", "application/json"); // Especificar el tipo de contenido como JSON
    request.setRawHeader("Authorization", "Bearer " + accessToken.toUtf8());
    request.setRawHeader("Content-Type", "application/json"); // Especificar el tipo de contenido como JSON

    // Crear el cuerpo de la solicitud utilizando variables
    QString atrPos = atr;                                          // ATR
    QString uuidPos = uuid;                                        // UUID
    QString pointOfSaleId = SessionManager::instance().getPosId(); // ID del punto de venta
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

    // Conectar la señal de respuesta usando la sintaxis antigua
    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(handlePostNetworkReply(QNetworkReply *)));

    // Enviar la solicitud POST
    manager->post(request, postData);
}

void ConfigScreen::handleMappedReply(QObject *replyObject)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(replyObject);
    if (reply)
    {
        //// Aquí manejas la respuesta del network manager
        handlePostNetworkReply(reply);
    }
}

void ConfigScreen::readWriteCardStepZero(std::vector<ParsedApduResponse> responseApdus)
{
    // Crear el manager de la red
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // Obtener el accessToken actual
    QString accessToken = SessionManager::instance().getCurrentAccessToken();

    // Crear la solicitud HTTP
    QNetworkRequest request;
    request.setUrl(QUrl("https://fleet.nebulae.com.co/api/external-network-gateway/rest/paymentMedium/applyPendingMods"));
    request.setRawHeader("accept", "application/json"); // Especificar el tipo de contenido como JSON
    request.setRawHeader("Authorization", "Bearer " + accessToken.toUtf8());
    request.setRawHeader("Content-Type", "application/json"); // Especificar el tipo de contenido como JSON

    // Crear el cuerpo de la solicitud utilizando variables
    QString atrPos = atrNumberConfig; // ATR
    QString uuidPos = uuidConfig.toUpper();
    // UUID
    QString pointOfSaleId = SessionManager::instance().getPosId(); // ID del punto de venta
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

void ConfigScreen::handlePostNetworkReply(QNetworkReply *reply)
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

                   /*  qDebug() << "responseLength Test" << responseLength;
 */
                    int status = _cReaderConfigScreen.customTransmit(cardReaderType, command, commandLength, response, &responseLength);

                    if (status != 0)
                    {
                        qDebug() << "Error en la transmisión:" << status;
                        // Manejar el error sin usar return
                        continue;
                    }

                    bool mplus;
                    if (atrNumberConfig.size() < 13 * 2)
                    {
                        mplus = true;
                    }

                    ApduResponse apduResponse = _cReaderConfigScreen.parseResponse(response, responseLength, mplus);

                    ParsedApduResponse parsedResponse = _cReaderConfigScreen.convertToParsedApduResponse(apduResponse, requestApdu);

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
    }
    // Liberar la memoria del objeto QNetworkReply
    reply->deleteLater();
}

void ConfigScreen::handlePostNetworkReplyZero(QNetworkReply *reply)
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
            if (nextStep.size() > 0)
            {
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

                        int status = _cReaderConfigScreen.customTransmit(cardReaderType, command, commandLength, response, &responseLength);

/*                         qDebug() << "responseLength Test" << responseLength;
 */                        if (status != 0)
                        {
                            qDebug() << "Error en la transmisión:" << status;
                            // Manejar el error sin usar return
                            continue;
                        }

                        bool mplus;
                        if (atrNumberConfig.size() < 13 * 2)
                        {
                            mplus = true;
                        }

                        ApduResponse apduResponse = _cReaderConfigScreen.parseResponse(response, responseLength, mplus);

                        ParsedApduResponse parsedResponse = _cReaderConfigScreen.convertToParsedApduResponse(apduResponse, requestApdu);

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
    }
    else
    {
        qDebug() << "Error en la solicitud:" << reply->errorString();
        QByteArray errorData = reply->readAll();
        qDebug() << "Detalle del error:" << errorData;
    }
    // Liberar la memoria del objeto QNetworkReply
    reply->deleteLater();
}

// Get ATR and UUID
void ConfigScreen::piccReader()
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
        printf("picc_open successful!\n");
    else
        printf("picc_open failed!\n");

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

        // Executar lectura-escritura FLEET
        readWriteCard(atrNumberConfig, uuidConfig.toUpper());
    }
    // picc_close();
}

// Data parser
QVariantMap ConfigScreen::parseJsonObject(const QString &jsonString)
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

QVariant ConfigScreen::parseJsonValue(const QString &jsonString)
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

QVariantList ConfigScreen::parseJsonArray(const QString &jsonString)
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

// Función para generar el contenido de "responseApdus"
QString ConfigScreen::generarResponseApdus(const std::vector<ParsedApduResponse> responseApdus)
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