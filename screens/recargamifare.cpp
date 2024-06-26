#include <QtGui>
#include "recargamifare.h"
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QFile>
#include <QFileInfo>
#include <QNetworkRequest>
#include <QStringList>
#include <QTimer>
#include <QUrl>
#include <QIntValidator>
#include <stdio.h>
#include "dialog/dialog.h"
#include <QVariantMap>
#include <QStringList>

#include <QtGui>
#include <QMessageBox>
#include <QVariantMap>
#include <QVariantList>
#include <QByteArray>
#include <QTextStream>
#include <QRegExp>

// Session Manager - Singleton
#include "sessionmanager.h"
#include <cstddef>

// String build
#include <iostream>
#include <sstream>
#include <iomanip>

// Custom Transmit
AcsReader _cReaderMifareScreen;

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

RecargaMifareScreen::RecargaMifareScreen(QWidget *parent)
    : QWidget(parent),
      timer(new QTimer(this))
/* networkManager(new QNetworkAccessManager(this)) */
{
    // Cards detect
    // connect(timer, SIGNAL(timeout()), this, SLOT(checkForCard()));

    // Icono en la parte izquierda de la pantalla
    QLabel *iconLabel = new QLabel;
    QPixmap iconPixmap(":/assets/icons/wallet.png");
    iconPixmap = iconPixmap.scaled(QSize(30, 30), Qt::KeepAspectRatio);
    iconLabel->setPixmap(iconPixmap);
    iconLabel->setStyleSheet("margin-top: -130px;");

    // Barra en el medio
    QLabel *barLabel = new QLabel;
    QPixmap barPixmap(":/assets/icons/div.png"); // Reemplaza ":/assets/bar.png" con la ruta a tu barra
    barLabel->setPixmap(barPixmap);
    barLabel->setStyleSheet("margin-right: 12px;");

    // Título centrado
    QLabel *titleLabel = new QLabel("Recarga Mifare");
    titleLabel->setFont(QFont("Arial", 14, QFont::Bold));
    titleLabel->setFixedWidth(150); // Ajusta el ancho según sea necesario
    titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    titleLabel->setWordWrap(true); // Permitir el ajuste de línea automático si el texto es demasiado largo

    addressText = new QLineEdit("2,000 COP"); // Inicializa addressText y asígnalo a la variable miembro

    // QLineEdit *addressText = new QLineEdit("20.000 COP");
    addressText->setPlaceholderText("Ingrese el valor de su recarga");
    addressText->setStyleSheet("border: 1px solid black; border-radius: 4px; font-size: 14pt;");
    addressText->setFixedWidth(150);
    addressText->setFixedHeight(40);

    // Botón de envío
    QPushButton *submitButton = new QPushButton();
    QIcon submitIcon(":/assets/icons/check_ok.png");
    submitButton->setIcon(submitIcon);
    submitButton->setIconSize(QSize(32, 32)); // Establece el tamaño del icono según sea necesario
    // addButton->setStyleSheet("border: 2px solid black; background-color: white;");
    submitButton->setStyleSheet("border: none");

    resultLabel = new QLabel;

    // Crear el QLabel para el texto de información
    infoText = new QLabel("Ubica la tarjeta en la lectora para continuar", this);
    infoText->setFont(QFont("Arial", 14));

    // Establece un ancho máximo
    int maxWidth = 300;
    infoText->setMaximumWidth(maxWidth);

    // Permite que el texto se envuelva
    infoText->setWordWrap(true);

    // Crear el QLabel para el texto "saldo actual"
    saldoLabel = new QLabel("SALDO ACTUAL:", this);
    saldoLabel->setFont(QFont("Arial", 14));
    saldoLabel->setVisible(false);
    saldoLabel->setMaximumWidth(600);
    saldoLabel->setWordWrap(true);

    // Crear el QLabel para el valor 1000
    valorLabel = new QLabel("1000", this);
    valorLabel->setVisible(false);
    valorLabel->setMaximumWidth(maxWidth);
    valorLabel->setWordWrap(true);

    // Crear el QLabel para el texto "saldo nuevo"
    saldoNuevoLabel = new QLabel("SALDO NUEVO:", this);
    saldoNuevoLabel->setStyleSheet("QLabel { color : green; }");
    saldoNuevoLabel->setVisible(false);
    saldoNuevoLabel->setMaximumWidth(maxWidth);
    saldoNuevoLabel->setWordWrap(true);

    // Crear el QLabel para el nuevo valor
    valorNuevoLabel = new QLabel("2000", this); // Ejemplo de nuevo valor
    valorNuevoLabel->setVisible(false);
    valorNuevoLabel->setMaximumWidth(maxWidth);
    valorNuevoLabel->setWordWrap(true);

    // Layout principal
    QGridLayout *mainLayout = new QGridLayout;

    // Agregar elementos al layout
    mainLayout->addWidget(iconLabel, 0, 0, 4, 1, Qt::AlignLeft);    // Icono en la esquina superior izquierda
    mainLayout->addWidget(barLabel, 0, 1, 4, 1, Qt::AlignCenter);   // Barra en el medio
    mainLayout->addWidget(titleLabel, 0, 2, 1, 2, Qt::AlignLeft);   // Título centrado horizontalmente
    mainLayout->addWidget(addressText, 1, 2, 1, 1, Qt::AlignRight); // Primer input a la derecha

    mainLayout->addWidget(submitButton, 2, 2, 1, 1, Qt::AlignRight); // Segundo input a la derecha
    mainLayout->addWidget(infoText, 3, 2, 1, 1, Qt::AlignCenter);    // Botón centrado debajo de los inputs
    mainLayout->addWidget(saldoLabel, 3, 2, 1, 1, Qt::AlignLeft);    // Botón centrado debajo de los inputs
    mainLayout->addWidget(valorLabel, 3, 3, 1, 1, Qt::AlignCenter);  // Botón centrado debajo de los inputs

    mainLayout->addWidget(saldoNuevoLabel, 4, 2, 1, 1, Qt::AlignCenter);
    mainLayout->addWidget(valorNuevoLabel, 4, 3, 1, 1, Qt::AlignCenter);

    setLayout(mainLayout);

    // Fullscreen
    setWindowState(windowState() ^ Qt::WindowFullScreen);

    // Signals and Slots (Events)

    // En el constructor de AddressBook en addressbook.cpp
    connect(submitButton, SIGNAL(clicked()), this, SLOT(piccReader()));

    /*
        Obtener el balance actual de la tarjeta del usuario con el evento
        textChange del input nameLine que corresponde al número de documento
        del usuario
    */
    // Convertir la cadena JSON en un objeto JSON

    // Conectar la función de validación al evento textChanged del QLineEdit
    connect(addressText, SIGNAL(textChanged(const QString &)), this, SLOT(validateAddressText(const QString &)));
}

void RecargaMifareScreen::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    timer->start(1000); // Empieza a escuchar cada segundo
    qDebug() << "Started listening for card reader";
}

void RecargaMifareScreen::hideEvent(QHideEvent *event)
{
    QWidget::hideEvent(event);
    timer->stop(); // Detiene la escucha
    qDebug() << "Stopped listening for card reader";
}

void RecargaMifareScreen::checkForCard()
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
        qDebug() << "Tarjeta Detectada";
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
    }
    else
    {
        qDebug() << "No se detectó ninguna tarjeta";
        // picc_close();
    }
}

// Get ATR and UUID
void RecargaMifareScreen::piccReader()
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

void RecargaMifareScreen::readWriteCard(const QString &atr, const QString &uuid)
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

void RecargaMifareScreen::readWriteCardStepZero(std::vector<ParsedApduResponse> responseApdus)
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

void RecargaMifareScreen::handlePostNetworkReply(QNetworkReply *reply)
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

                    int status = _cReaderMifareScreen.customTransmit(cardReaderType, command, commandLength, response, &responseLength);

                    if (status != 0)
                    {
                        qDebug() << "Error en la transmisión:" << status;
                        // Manejar el error sin usar return
                        continue;
                    }

                    // Validar si la tarjeta es Mifare Plus
                    bool mplus;
                    if (atrNumberConfig.size() < 13 * 2)
                    {
                        qDebug() << "mplus" << atrNumberConfig.size();
                        qDebug() << "13 * 2" << 13 * 2;
                        mplus = true;
                    }

                    ApduResponse apduResponse = _cReaderMifareScreen.parseResponse(response, responseLength, mplus);

                    ParsedApduResponse parsedResponse = _cReaderMifareScreen.convertToParsedApduResponse(apduResponse, requestApdu);

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

void RecargaMifareScreen::handlePostNetworkReplyZero(QNetworkReply *reply)
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
                {
                    QString step = nextStep["step"].toString();
                    if (step.isNull())
                    {
                        QString error = nextStep["error"].toString();
                        qDebug() << "error" << error;
                        picc_close();
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

                        int status = _cReaderMifareScreen.customTransmit(cardReaderType, command, commandLength, response, &responseLength);

                        if (status != 0)
                        {
                            qDebug() << "Error en la transmisión:" << status;
                            // Manejar el error sin usar return
                            continue;
                        }

                        // Validar si la tarjeta es Mifare Plus
                        bool mplus;
                        if (atrNumberConfig.size() < 13 * 2)
                        {
                            qDebug() << "mplus" << atrNumberConfig.size();
                            qDebug() << "13 * 2" << 13 * 2;
                            mplus = true;
                        }

                        ApduResponse apduResponse = _cReaderMifareScreen.parseResponse(response, responseLength, mplus);

                        ParsedApduResponse parsedResponse = _cReaderMifareScreen.convertToParsedApduResponse(apduResponse, requestApdu);

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
        if (cardDataMap.contains("appliedMods"))
        {

            QString appliedModsHandle = cardDataMap["appliedMods"].toString();

            QVariantMap appliedModsMap = parseJsonObject(appliedModsHandle);

            if (appliedModsMap.contains("id"))
            {
                QString id = appliedModsMap["id"].toString();
                qDebug() << "id" << id;
            }
            if (appliedModsMap.contains("ts"))
            {
                QString ts = appliedModsMap["ts"].toString();
                qDebug() << "ts" << ts;
            }
            if (appliedModsMap.contains("applied"))
            {
                QString applied = appliedModsMap["applied"].toString();
                qDebug() << "applied" << applied;
            }

            if (appliedModsMap.contains("payload"))
            {
                QVariantMap payload = appliedModsMap["payload"].toMap();
                if (payload.contains("pocket"))
                {
                    QString pocket = payload["pocket"].toString();
                    qDebug() << "pocket" << pocket;
                }
                if (payload.contains("value"))
                {
                    QString value = payload["value"].toString();
                    qDebug() << "value" << value;
                }
                if (payload.contains("saleId"))
                {
                    QString saleId = payload["saleId"].toString();
                    qDebug() << "saleId" << saleId;
                }
                if (payload.contains("saleTime"))
                {
                    QString saleTime = payload["saleTime"].toString();
                    qDebug() << "saleTime" << saleTime;
                }
            }
            // Cerrar lectora
            picc_close();
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

void RecargaMifareScreen::handleSubmit()
{
    //    emit loginSuccessful();
    qDebug() << "Probando recarga de billetera" << "Estamo activos";
}

// Función para manejar el cambio de texto en el QLineEdit
void RecargaMifareScreen::handleTextChanged(const QString &text)
{
    // Realizar acciones en respuesta al cambio de texto
    qDebug() << "Texto cambiado:" << text;
    // Puedes realizar cualquier acción adicional que desees con el texto cambiado, como actualizar otras partes de la interfaz de usuario o realizar alguna lógica de validación.
}

QVariantMap RecargaMifareScreen::stringToJson(const QString &jsonString)
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

QVariant RecargaMifareScreen::parseJsonValue(const QString &jsonString)
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

QVariantList RecargaMifareScreen::parseJsonArray(const QString &jsonString)
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

/* void RecargaMifareScreen::getCurrentBalance(const QString &text)
{

    // Validar que la longitud del texto sea de 10 dígitos
    if (text.length() == 10 && text.toInt() != 0) // Asegúrate de que es un número válido
    {
        qDebug() << "Longitud válida de 10 dígitos.";
        QString jwtToken = SessionManager::instance().getJwtToken();

        // Obtener el valor de nameLine como el documento
        QString document = nameLine->text();

        qDebug() << "User Document." << document;
        SessionManager::instance().setCurrentUserDocument(document);

        // Convertir jwtToken a un objeto JSON utilizando stringToJson
        QVariantMap jwtTokenJson = stringToJson(jwtToken);
        QString accessToken = jwtTokenJson.value("access_token").toString();

        qDebug()
            << "jwt." << jwtToken;
        qDebug() << "jwtTokenJson" << jwtTokenJson;
        qDebug() << "accessToken" << accessToken;

        // Crear la URL con el parámetro document
        QString url = QString("https://fleet.nebulae.com.co/api/external-network-gateway/rest/endUser/findByDocument?documentType=CITIZENSHIP_CARD&document=%1").arg(document);

        // Crear el manager de la red
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);

        // Conectar la señal de respuesta usando la sintaxis antigua
        connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(handleNetworkReply(QNetworkReply *)));

        // Crear la solicitud HTTP
        QNetworkRequest request;
        request.setUrl(QUrl(url));
        request.setRawHeader("Authorization", "Bearer " + accessToken.toUtf8());
        request.setRawHeader("Accept", "application/json"); // Especificar que esperas una respuesta JSON

        // Enviar la solicitud
        manager->get(request);
    }
    else
    {
        qDebug() << "Longitud inválida, debe ser de 10 dígitos.";
    }
}
 */
void RecargaMifareScreen::updateSaldoLabel(int balance, const QString &response)
{
    // Crear el texto con HTML para estilizar el balance en rojo
    QLocale locale = QLocale::system();
    QString formattedBalance = locale.toString(balance);
    QString text = QString("");
    // Iniciar un temporizador de 5 segundos para restablecer el contenido inicial de saldoText
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(restoreSaldoLabel()));

    if (balance < 0)
        text = QString("SALDO ACTUAL: <span style='color:red;'>%1 COP</span>").arg(formattedBalance);
    else if (response != "no")
    {
        text = QString("<span style='color:red;'>%1</span>").arg(response);
        timer->start(5000);
    }
    else
        text = QString("SALDO ACTUAL: %1 COP").arg(formattedBalance);

    infoText->setVisible(false);
    saldoLabel->setVisible(true);
    saldoLabel->setText(text);
}

void RecargaMifareScreen::restoreSaldoLabel()
{
    infoText->setVisible(true);
    saldoLabel->setVisible(false);
}

/* void RecargaMifareScreen::handleNetworkReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        // Leer la respuesta
        QByteArray responseData = reply->readAll();
        qDebug() << "Response:" << responseData;

        // Asignar la respuesta a la variable currentBalance
        currentBalance = QString(responseData);

        QVariantMap balanceJsonMap = parseJsonObject(currentBalance);
        if (balanceJsonMap.contains("fullName"))
            userName = balanceJsonMap["fullName"].toString();
        userDocument = nameLine->text();

        if (balanceJsonMap.contains("id"))
        {
            userId = balanceJsonMap["id"].toString();
            SessionManager::instance().setCurrentUserId(userId);
        }

        if (balanceJsonMap.contains("wallet"))
        {
            QVariantMap wallet = balanceJsonMap["wallet"].toMap();
            if (wallet.contains("pockets"))
            {
                QVariantMap pockets = wallet["pockets"].toMap();
                if (pockets.contains("REGULAR"))
                {
                    QVariantMap regularPocket = pockets["REGULAR"].toMap();
                    if (regularPocket.contains("balance"))
                    {
                        int balance = regularPocket["balance"].toInt();
                        qDebug() << "Balance: " << balance;
                        QString response = QString("no");
                        QMetaObject::invokeMethod(this, "updateSaldoLabel", Q_ARG(int, balance), Q_ARG(const QString &, response));
                    }
                }
            }
        }
    }
    else
    {
        qDebug() << "Error en la solicitud:" << reply->errorString();
        QString response = QString("Error al obtener el saldo de este usuario");
        int balance = 666;
        QMetaObject::invokeMethod(this, "updateSaldoLabel", Q_ARG(int, balance), Q_ARG(const QString &, response));
    }

    // Liberar la memoria del objeto QNetworkReply
    reply->deleteLater();
}
 */
void RecargaMifareScreen::validateAddressText(const QString &text)
{
    QString modifiedText;

    // Eliminar caracteres no deseados del texto (permitir solo números, un punto decimal y el sufijo "COP")
    for (int i = 0; i < text.size(); ++i)
    {
        QChar ch = text.at(i);
        if (ch.isDigit() || ch == '.' || (ch == ' ' && text.mid(i) == " COP"))
        {
            modifiedText.append(ch);
        }
    }

    // Verificar si el sufijo "COP" está presente al final del texto
    if (!modifiedText.endsWith(" COP"))
    {
        modifiedText += " COP";
    }

    // Formatear el número con coma para las milesimas si es necesario
    QString amount = modifiedText.left(modifiedText.indexOf(" COP"));
    QString formattedAmount;
    int value = amount.toInt();
    if (value >= 1000)
    {
        formattedAmount = QString::number(value);

        // Insertar comas cada 1.000 unidades
        int separatorPos = formattedAmount.length() % 3;
        if (separatorPos == 0)
        {
            separatorPos = 3;
        }
        while (separatorPos < formattedAmount.length())
        {
            formattedAmount.insert(separatorPos, ',');
            separatorPos += 4; // Moverse cuatro caracteres para llegar al siguiente grupo de tres dígitos
        }
    }
    else
    {
        formattedAmount = amount;
    }

    // Reemplazar el texto original con el texto formateado
    modifiedText.replace(0, modifiedText.indexOf(" COP"), formattedAmount);

    // Verificar la posición del cursor y ajustarla si es necesario
    int cursorPosition = addressText->cursorPosition();
    int formattedAmountLength = formattedAmount.length();
    if (cursorPosition < formattedAmountLength)
    {
        // Si el cursor está dentro del texto formateado, ajustar la posición del cursor en el texto original
        int commaCount = formattedAmount.count(',');
        int originalCursorPosition = cursorPosition - commaCount; // Ajustar la posición del cursor considerando las comas
        int originalTextLength = amount.length();
        if (originalCursorPosition < originalTextLength)
        {
            // Si el cursor está dentro del texto original, ajustar la posición del cursor en el texto modificado
            int commaCountInOriginal = amount.left(originalCursorPosition).count(',');
            cursorPosition = originalCursorPosition + commaCountInOriginal;
        }
        else
        {
            // Si el cursor está después del texto original, ajustar la posición del cursor en el sufijo "COP"
            cursorPosition = modifiedText.indexOf(" COP");
        }
    }
    else
    {
        // Si el cursor está después del texto formateado, ajustar la posición del cursor en el sufijo "COP"
        cursorPosition = modifiedText.indexOf(" COP");
    }

    // Actualizar el texto y la posición del cursor en el QLineEdit
    addressText->blockSignals(true); // Bloquea las señales para evitar la recursión
    addressText->setText(modifiedText);
    addressText->setCursorPosition(cursorPosition);
    addressText->blockSignals(false); // Desbloquea las señales
}

QString RecargaMifareScreen::extractNumericValue(const QString &text)
{
    QString result = text;

    // Eliminar el sufijo "COP"
    result.replace("COP", "", Qt::CaseInsensitive);

    // Eliminar comas
    result.remove(',');

    // Eliminar puntos decimales
    result.remove('.');

    // Eliminar espacios en blanco
    result = result.trimmed();

    return result;
}

void RecargaMifareScreen::executeSale(const QString &)
{
}

int RecargaMifareScreen::removeCommasAndConvertToInt(const QString &priceString)
{
    // Remover las comas del string
    QString priceWithoutCommas = priceString;
    priceWithoutCommas.remove(',');

    // Convertir el string a un entero
    bool ok;
    int price = priceWithoutCommas.toInt(&ok);

    // Verificar si la conversión fue exitosa
    if (!ok)
    {
        qWarning() << "Error: No se pudo convertir el string a un entero";
        // En este caso, podrías devolver un valor predeterminado o lanzar una excepción
    }

    return price;
}

void RecargaMifareScreen::keyPressEvent(QKeyEvent *event)
{
    QLineEdit *currentLineEdit = dynamic_cast<QLineEdit *>(focusWidget());
    QString text = currentLineEdit->text();
    int cursorPosition = currentLineEdit->cursorPosition();

    switch (event->key())
    {
    case Qt::Key_Return:
    {
        // Crear una instancia del diálogo de respuesta del servidor
        ResponseDialog *responseDialog = new ResponseDialog();

        // Configurar el icono de respuesta en el dialogo
        QIcon responseIcon(":/assets/icons/dialog/alert.png");
        responseDialog->setResponseIcon(responseIcon);

        // Configurar el texto de respuesta en el diálogo
        responseDialog->setResponseText("Confirmar venta", "yes");

        // Eliminar sufijo COP y espacios en blanco addressText antes de mostrar el mensaje
        QString saleAmmount = addressText->text();

        // Eliminar el sufijo "COP"
        saleAmmount.replace("COP", "", Qt::CaseInsensitive);

        // Eliminar espacios en blanco
        saleAmmount = saleAmmount.trimmed();

        // revisar variable que contiene el valor deseado para la recarga
        qDebug() << "removeCommasAndConvertToInt + saleAmmount" << removeCommasAndConvertToInt(saleAmmount);

        // Valor de la venta en el singleton
        SessionManager::instance().setCurrentUnitPrice(removeCommasAndConvertToInt(saleAmmount));

        // Agregar texto adicional con información sobre la venta
        QString additionalText = QString("Producto: Recarga Billetera\n") +
                                 QString("Usuario: " + userName + "\n") +
                                 QString("Documento: " + userDocument + "\n") +
                                 QString("Valor: ") + saleAmmount + " COP";

        responseDialog->setAdditionalText(additionalText);

        // Configurar el texto de respuesta para el botón en el diálogo
        responseDialog->setCloseButtonText("Confirmar");

        responseDialog->setCancelButtonText("Cancelar");

        /*
            Conectar la señal 'saleSuccess()' de responseDialog al slot 'emitSaleSuccessToMainWindow()'
            que emite la señal 'showSaleScreen()' en MainWindow.

        */
        connect(responseDialog, SIGNAL(saleSuccess()), this, SLOT(emitSaleSuccessToMainWindow()));

        // Mostrar el diálogo de respuesta del servidor
        responseDialog->exec();

        // Eliminar la instancia del diálogo después de que se haya cerrado
        delete responseDialog;
        qDebug() << "Return key pressed ";
        break;
    }
    case Qt::Key_F1:
        // Mover el cursor a la izquierda
        if (cursorPosition > 0)
        {
            currentLineEdit->setCursorPosition(cursorPosition - 1);
        }
        break;
    case Qt::Key_F4:
        // Mover el cursor a la derecha
        if (cursorPosition < text.size())
        {
            currentLineEdit->setCursorPosition(cursorPosition + 1);
        }
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}

void RecargaMifareScreen::emitSaleSuccessToMainWindow()
{
    qDebug() << "Widget Confirmación recarga billetera";
    emit showSaleScreen();
}

void RecargaMifareScreen::emitSaleErrorToMainWindow()
{
}

// Data parser
QVariantMap RecargaMifareScreen::parseJsonObject(const QString &jsonString)
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

// Función para generar el contenido de "responseApdus"
QString RecargaMifareScreen::generarResponseApdus(const std::vector<ParsedApduResponse> responseApdus)
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