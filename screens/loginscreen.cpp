#include <QtGui>
#include "loginscreen.h"
#include <QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QFile>
#include <QFileInfo>
#include <QNetworkRequest>
#include <QStringList>
#include <QTimer>
#include <QUrl>
#include <stdio.h>
#include "dialog/dialog.h"
#include "sessionmanager.h"
#include <QVariantMap>
#include <QStringList>

LoginScreen::LoginScreen(QWidget *parent)
    : QWidget(parent)
{
    /* nameLine = new QLineEdit("cajero.pos@nebulae.com.co"); */
    nameLine = new QLineEdit("cajero@nebulae.com.co");

    // Configura otras propiedades del QLineEdit si es necesario
    nameLine->setPlaceholderText("Ingrese su usuario"); // Texto de marcador de posición
    nameLine->setFixedWidth(200);                       // Cambia 220 al ancho deseado en píxeles
    nameLine->setFixedHeight(40);                       // Cambia 40 al ancho deseado en píxeles
    nameLine->setStyleSheet("border: 1px solid black; border-radius: 4px;");

    // Establece el foco de entrada en el QLineEdit
    nameLine->setFocus();

    // Creamos una instancia de QTextLine
    QLabel *titleLabel = new QLabel("NebulaE");
    titleLabel->setFont(QFont("Arial", 16, QFont::Bold));
    /* addressText = new QLineEdit("cajero.pos@nebulae.com.co"); */
    addressText = new QLineEdit("cajero@nebulae.com.co");
    addressText->setEchoMode(QLineEdit::Password); // Establece el modo de eco como contraseña
    addressText->setStyleSheet("border: 1px solid black; border-radius: 4px;");
    addressText->setPlaceholderText("Ingrese su clave"); // Texto de marcador de posición
    addressText->setFixedWidth(200);                     // Cambia 200 al ancho deseado en píxeles
    addressText->setFixedHeight(40);                     // Cambia 40 al ancho deseado en píxeles

    QPushButton *submitButton = new QPushButton(tr("Iniciar"));
    submitButton->setFixedWidth(200); // Cambia 220 al ancho deseado en píxeles
    submitButton->setStyleSheet("border: 1px solid black; border-radius: 4px; font-size: 14pt;");
    submitButton->setFixedHeight(40); // Cambia 40 al ancho deseado en píxeles

    // Inicializa la variable miembro resultLabel en lugar de declarar una nueva localmente
    resultLabel = new QLabel;

    QGridLayout *mainLayout = new QGridLayout;

    // Barra de notificaciones en la fila 0
    QHBoxLayout *notificationBarLayout = new QHBoxLayout;

    QLabel *networkIcon = new QLabel;
    QPixmap pixmapNetwork(":/assets/icons/config/interface-essential-wifi-feed.png");
    pixmapNetwork = pixmapNetwork.scaled(QSize(16, 16), Qt::KeepAspectRatio);
    networkIcon->setPixmap(pixmapNetwork);
    networkIcon->setStyleSheet("border: none;");
    notificationBarLayout->addWidget(networkIcon);

    QLabel *chargeIcon = new QLabel;
    QPixmap pixmapCharge(":/assets/icons/notificaciones/charge.png");
    pixmapCharge = pixmapCharge.scaled(QSize(24, 24), Qt::KeepAspectRatio);
    chargeIcon->setPixmap(pixmapCharge);
    chargeIcon->setStyleSheet("border: none; margin-top: 1px;");
    notificationBarLayout->addWidget(chargeIcon);

    notificationBarContainer = new QWidget(this);
    notificationBarContainer->setLayout(notificationBarLayout);
    notificationBarLayout->setAlignment(Qt::AlignRight);

    // Establece la política de expansión horizontal para que el contenedor ocupe todo el ancho de la ventana
    notificationBarContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    mainLayout->addWidget(notificationBarContainer, 0, 0, 1, 2); // Agrega notificationBarContainer al principio del layout

    // Agregar el título en la segunda fila y centrarlo horizontalmente
    mainLayout->addWidget(titleLabel, 1, 0, 1, 2, Qt::AlignCenter);

    // Agregar nameLine en la tercera fila
    mainLayout->addWidget(nameLine, 2, 0, 1, 2, Qt::AlignCenter);

    // Agregar addressText en la cuarta fila
    mainLayout->addWidget(addressText, 3, 0, 1, 2, Qt::AlignCenter);

    // Agregar un espacio en blanco entre addressText y submitButton
    QSpacerItem *spacer2 = new QSpacerItem(20, 10, QSizePolicy::Preferred, QSizePolicy::Fixed); // Aumentar el tamaño del segundo espacio
    mainLayout->addItem(spacer2, 4, 0);
    // Agrega el espacio en la quinta fila, primera columna                                                 // Agrega el espacio en la quinta fila, primera columna

    // Agregar submitButton en la sexta fila
    mainLayout->addWidget(submitButton, 5, 0, 1, 2, Qt::AlignCenter);

    // Agregar resultLabel en la séptima fila y centrarlo horizontalmente
    mainLayout->addWidget(resultLabel, 6, 0, 1, 2, Qt::AlignCenter);

    setLayout(mainLayout);
    setWindowTitle(tr("Nebula E POS"));

    // Fullscreen
    setWindowState(windowState() ^ Qt::WindowFullScreen);

    // Signals and Slots (Events)

    // En el constructor de AddressBook en addressbook.cpp
    connect(submitButton, SIGNAL(clicked()), this, SLOT(handleSubmit()));

    // Conecta el evento de teclado al QLineEdit
    connect(nameLine, SIGNAL(textChanged(const QString &)), this, SLOT(handleTextChanged(const QString &)));
}

void LoginScreen::handleSubmit()
{
    //  Obtener los valores de usuario y clave
    QString username = nameLine->text();
    QString password = addressText->text();

    // Crear el objeto QNetworkAccessManager
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // Crear los parámetros del cuerpo de la solicitud
    QByteArray postData;
    postData.append("grant_type=password&");
    postData.append("scope=openid&");
    /* postData.append("username=cajero.pos@nebulae.com.co&");
    postData.append("password=cajero.pos@nebulae.com.co&"); */
    postData.append("username=" + QUrl::toPercentEncoding(username) + "&");
    postData.append("password=" + QUrl::toPercentEncoding(password) + "&");
    postData.append("client_id=emi");

    // Crear la solicitud HTTP
    QNetworkRequest request(QUrl("https://fleet.nebulae.com.co/auth/realms/FLEET/protocol/openid-connect/token"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Realizar la solicitud POST
    QNetworkReply *reply = manager->post(request, postData);

    // Conectar la señal para manejar la respuesta cuando esté lista
    connect(reply, SIGNAL(finished()), this, SLOT(handleNetworkReply()));
}

void LoginScreen::handleNetworkReply()
{
    // Obtener el objeto QNetworkReply
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (reply)
    {
        // Verificar si la solicitud tuvo éxito
        if (reply->error() == QNetworkReply::NoError)
        {
            // Leer la respuesta
            QByteArray responseData = reply->readAll();

            // Almacenar la respuesta en la variable de clase jwtToken
            jwtToken = responseData;

            // Enviar el jwtToken al singleton
            SessionManager::instance().setJwtToken(jwtToken);

            // Convertir jwtToken a un objeto JSON utilizando stringToJson
            QVariantMap jwtTokenJson = stringToJson(jwtToken);
            QString accessToken = jwtTokenJson.value("access_token").toString();
            QString refreshToken = jwtTokenJson.value("refresh_token").toString();

            // Enviar el accessToken al singleton
            SessionManager::instance().setAccessToken(accessToken);

            // Enviar el refreshToken al singleton
            SessionManager::instance().setRefreshToken(refreshToken);

            // Crear la URL para consulta get pointOfSale
            QString url = QString("https://fleet.nebulae.com.co/api/external-network-gateway/rest/pointOfSale");

            // Crear el manager de la red
            QNetworkAccessManager *managerPOS = new QNetworkAccessManager(this);

            // Conectar la señal de respuesta usando la sintaxis antigua
            connect(managerPOS, SIGNAL(finished(QNetworkReply *)), this, SLOT(handleSecondaryNetworkReply(QNetworkReply *)));

            // Crear la solicitud HTTP
            QNetworkRequest request;
            request.setUrl(QUrl(url));
            request.setRawHeader("Authorization", "Bearer " + accessToken.toUtf8());
            request.setRawHeader("Accept", "application/json"); // Especificar que esperas una respuesta JSON

            // Enviar la solicitud
            managerPOS->get(request);

            qDebug() << "Response" << jwtToken;

            // Liberar la memoria del objeto QNetworkReply
            reply->deleteLater();

            // Crear una instancia del diálogo de respuesta del servidor
            ResponseDialog *responseDialog = new ResponseDialog();

            // Configurar el icono de respuesta en el dialogo
            QIcon responseIcon(":/assets/icons/dialog/email-emoji-smile-smart.png");
            responseDialog->setResponseIcon(responseIcon);

            // Configurar el texto de respuesta en el diálogo
            responseDialog->setResponseText("Usuario autenticado correctamente.", "no");

            // Configurar el texto de respuesta para el botón en el diálogo
            responseDialog->setCloseButtonText("Continuar");

            /*
                Conectar la señal 'loginSuccess()' de responseDialog al slot 'emitLoginSuccessToMainWindow()'
                que emite la señal 'submitClicked()' en MainWindow.

            */
            connect(responseDialog, SIGNAL(loginSuccess()), this, SLOT(emitLoginSuccessToMainWindow()));

            // Mostrar el diálogo de respuesta del servidor
            responseDialog->exec();

            // Eliminar la instancia del diálogo después de que se haya cerrado
            delete responseDialog;
        }
        else
        {

            // Crear una instancia del diálogo de respuesta del servidor
            ResponseDialog *responseDialog = new ResponseDialog();

            // Configurar el icono de respuesta en el dialogo
            QIcon responseIcon(":/assets/icons/dialog/phone-actions-remove-2.png");
            responseDialog->setResponseIcon(responseIcon);

            // Configurar el texto de respuesta en el diálogo
            responseDialog->setResponseText("Estamos teniendo problemas para autenticas a este usuario.", "no");

            // Configurar el texto de respuesta para el botón en el diálogo
            responseDialog->setCloseButtonText("Intenta nuevamente");

            /*
                Conectar la señal 'loginError()' de responseDialog al slot 'emitLoginErrorToMainWindow()'
                que emite la señal 'submitClicked()' en MainWindow.

            */
            connect(responseDialog, SIGNAL(loginError()), this, SLOT(emitLoginErrorToMainWindow()));

            // Mostrar el diálogo de respuesta del servidor
            responseDialog->exec();

            // Eliminar la instancia del diálogo después de que se haya cerrado
            delete responseDialog;

            // Manejar el error
            qDebug() << "Error en la solicitud:" << reply->errorString();
        }
    }
}

void LoginScreen::handleSecondaryNetworkReply(QNetworkReply *reply)
{
    if (reply)
    {
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray responseData = reply->readAll();

            // Allmacenar la respuesta en el SessionManager
            SessionManager::instance().setPointOfSaleData(responseData);
            qDebug() << "Aqui estoy enviando la data del POS" << responseData;
            emitLoginSuccessToMainWindow();

            qDebug() << "POS data" << responseData;
        }
        else
        {
            qDebug() << "Error en la solicitud secundaria:" << reply->errorString();
        }
        reply->deleteLater();
    }
}

QVariantMap LoginScreen::stringToJson(const QString &jsonString)
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

// Función para manejar el cambio de texto en el QLineEdit
void LoginScreen::handleTextChanged(const QString &text)
{
    // Realizar acciones en respuesta al cambio de texto
    qDebug() << "Texto cambiado:" << text;
    // Puedes realizar cualquier acción adicional que desees con el texto cambiado, como actualizar otras partes de la interfaz de usuario o realizar alguna lógica de validación.
}

void LoginScreen::emitLoginSuccessToMainWindow()
{
    emit submitClicked();
}

void LoginScreen::emitLoginErrorToMainWindow()
{
    emit authFailed();
}
