#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtGui>
#include <QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QFile>
#include <QFileInfo>
#include <QNetworkRequest>
#include <QStringList>
#include <QTimer>
#include <QUrl>
#include <QIcon>
#include <QDir>
#include <QGraphicsOpacityEffect>
#include <stdio.h>

#include "screens/sessionmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      currentIndex(0),
      refreshTimer(new QTimer(this))
{
    // Inicializa la variable de autenticación en false
    isAuthenticated = false;

    // Configurar el temporizador para que se dispare cada 15 minutos (900 segundos) - refreshToken
    connect(refreshTimer, SIGNAL(timeout()), this, SLOT(refreshToken()));
    refreshTimer->start(900 * 1000); // 900 segundos en milisegundos

    // Configurar el color de fondo
    this->setStyleSheet("background-color: white;");

    button1 = new QPushButton;
    QIcon homeIcon(":/assets/icons/home.png");
    button1->setIcon(homeIcon);
    button1->setIconSize(QSize(32, 32)); // Establece el tamaño del icono según sea necesario
    button1->setStyleSheet("border: 2px solid black; background-color: white;");

    button2 = new QPushButton;
    QIcon productIcon(":/assets/icons/products.png");
    button2->setIcon(productIcon);
    button2->setIconSize(QSize(32, 32)); // Establece el tamaño del icono según sea necesario
    button2->setStyleSheet("border: 2px solid black; background-color: white;");

    button3 = new QPushButton;
    QIcon recargaIcon(":/assets/icons/historial.png");
    button3->setIcon(recargaIcon);
    button3->setIconSize(QSize(32, 32)); // Establece el tamaño del icono según sea necesario
    button3->setStyleSheet("border: 2px solid black; background-color: white;");

    button4 = new QPushButton;
    QIcon configIcon(":/assets/icons/config.png");
    button4->setIcon(configIcon);
    button4->setIconSize(QSize(32, 32)); // Establece el tamaño del icono según sea necesario
    // Establece una hoja de estilo para el botón
    button4->setStyleSheet("border: 2px solid black; background-color: white;");

    stackedWidget = new QStackedWidget;
    loginScreen = new LoginScreen;
    responseDialog = new ResponseDialog(this);
    homeScreen = new HomeScreen;
    productScreen = new ProductScreen;
    recargaBilleteraScreen = new RecargaBilleteraScreen;
    recargaMifareScreen = new RecargaMifareScreen;
    saleProgress = new SaleProgress;
    mifareSaleProgress = new MifareSaleProgress;
    saleSuccess = new SaleSuccess;
    saleError = new SaleError;
    mifareSaleSuccess = new MifareSaleSuccess;
    mifareSaleError = new MifareSaleError;
    historyScreen = new HistoryScreen;
    configScreen = new ConfigScreen;
    wifiScreen = new WifiScreen;
    wifiConnectScreen = new WifiConnectScreen;

    // Agregar las pantallas al arreglo - cambio de pantalla via keypad
    screens << homeScreen << productScreen << historyScreen << configScreen;

    stackedWidget->addWidget(loginScreen);
    stackedWidget->addWidget(homeScreen);
    stackedWidget->addWidget(productScreen);
    stackedWidget->addWidget(recargaBilleteraScreen);
    stackedWidget->addWidget(recargaMifareScreen);
    stackedWidget->addWidget(saleProgress);
    stackedWidget->addWidget(mifareSaleProgress);
    stackedWidget->addWidget(mifareSaleSuccess);
    stackedWidget->addWidget(mifareSaleError);
    stackedWidget->addWidget(saleSuccess);
    stackedWidget->addWidget(saleError);
    stackedWidget->addWidget(historyScreen);
    stackedWidget->addWidget(configScreen);
    stackedWidget->addWidget(wifiScreen);
    stackedWidget->addWidget(wifiConnectScreen);

    // connect(button1, SIGNAL(clicked()), this, SLOT(showLoginScreen()));
    connect(button1, SIGNAL(clicked()), this, SLOT(showHomeScreen()));
    connect(button2, SIGNAL(clicked()), this, SLOT(showProductScreen()));
    connect(button3, SIGNAL(clicked()), this, SLOT(showHistoryScreen()));
    connect(button4, SIGNAL(clicked()), this, SLOT(showConfigScreen()));

    // Conectar la señal 'submitClicked()' de responseDialog con el slot 'setAuthenticated()' de mainwindow
    connect(loginScreen, SIGNAL(submitClicked()), this, SLOT(setAuthenticated()));

    // Conectar la señal 'showSaleScreen()' de recargaBilleteraScreen con el slot 'changeToSaleScreen()' de mainwindow
    connect(recargaBilleteraScreen, SIGNAL(showSaleScreen()), this, SLOT(changeToSaleScreen()));

    // Conectar la señal 'showMifareSaleScreen()' de recargaMifareScreen con el slot 'changeToMifareSaleScreen()' de mainwindow
    connect(recargaMifareScreen, SIGNAL(showMifareSaleScreen()), this, SLOT(changeToMifareSaleScreen()));

    // Conectar la señal 'progressDoneSuccess()' de SaleProgress con el slot 'changeToSaleScreen()' de mainwindow
    connect(saleProgress, SIGNAL(progressDoneSuccess()), this, SLOT(changeToSaleSuccessScreen()));

    // Conectar la señal 'progressMifareDoneSuccess()' de MifareSaleProgress con el slot 'changeToMifareSaleSuccessScreen()' de mainwindow
    connect(mifareSaleProgress, SIGNAL(progressMifareDoneSuccess()), this, SLOT(changeToMifareSaleSuccessScreen()));

    // Conectar la señal 'progressDoneError()' de SaleProgress con el slot 'changeToSaleScreen()' de mainwindow
    connect(saleProgress, SIGNAL(progressDoneError()), this, SLOT(changeToSaleErrorScreen()));

    // Conectar la señal 'progressMifareDoneError()' de SaleProgress con el slot 'changeToMifareSaleErrorScreen()' de mainwindow
    connect(mifareSaleProgress, SIGNAL(progressMifareDoneError()), this, SLOT(changeToMifareSaleErrorScreen()));

    // Conectar la señal 'backToBilleteraScreen()' de SaleSuccess con el slot 'changeBackToRecargaBilletera()' de mainwindow
    connect(saleSuccess, SIGNAL(backToBilleteraScreen()), this, SLOT(changeBackToRecargaBilletera()));

    // Conectar la señal 'backToBilleteraScreen()' de SaleError con el slot 'changeBackToRecargaBilletera()' de mainwindow
    connect(saleError, SIGNAL(backToBilleteraScreen()), this, SLOT(changeBackToRecargaBilletera()));

    // Conectar la señal 'backToMifareScreen()' de MifareSaleSuccess con el slot 'changeBackToRecargaBilletera()' de mainwindow
    connect(mifareSaleSuccess, SIGNAL(backToMifareScreen()), this, SLOT(changeBackToRecargaMifare()));

    // Conectar la señal 'backToMifareScreen()' de MifareSaleError con el slot 'changeBackToRecargaMifare()' de mainwindow
    connect(mifareSaleError, SIGNAL(backToMifareScreen()), this, SLOT(changeBackToRecargaMifare()));

    // Conectar la señal 'backToMifareSaleProgress()' de MifareSaleError con el slot 'changeToMifareSaleScreen()' de mainwindow
    connect(mifareSaleError, SIGNAL(backToMifareSaleProgressScreen()), this, SLOT(changeToMifareSaleScreen()));

    // Conectar la señal 'authFailed()' de loginScreen con el slot 'setNotAuthenticated()' de mainwindow
    connect(loginScreen, SIGNAL(authFailed()), this, SLOT(setNotAuthenticated()));

    // Conectar la señal 'submitClickd()' de productscreen con el slot 'showRecargaBilleteraScreen()' de mainwindow
    connect(productScreen, SIGNAL(selectedProduct()), this, SLOT(showRecargaBilleteraScreen()));

    // Conectar la señal 'submitClickd()' de productscreen con el slot 'showRecargaMifareScreen()' de mainwindow
    connect(productScreen, SIGNAL(selectedProductMifare()), this, SLOT(showRecargaMifareScreen()));

    // Conectar la señal 'changeToWifiSetup()' de configScreen con el slot 'changeToWifiScreen()' de mainwindow
    connect(configScreen, SIGNAL(changeToWifiSetup()), this, SLOT(changeToWifiScreen()));

    // Conectar la señal 'changeToWifiConnect()' de wifiScreen con el slot 'changeToWifiConnectScreen()' de mainwindow
    connect(wifiScreen, SIGNAL(changeToWifiConnect()), this, SLOT(changeToWifiConnectScreen()));

    // Fullscreen
    setWindowState(windowState() ^ Qt::WindowFullScreen);

    // Configurar el diseño de la interfaz
    QGridLayout *mainLayout = new QGridLayout;

    // Barra de notificaciones en la fila 0
    QHBoxLayout *notificationBarLayout = new QHBoxLayout;

    // Número serial del POS
    QLabel *serialPos = new QLabel;
    serialPos->setText("ZS544587");
    serialPos->setStyleSheet("font-size: 10pt; border: none;");

    // Agrega el serial pos a la barra de notificaciones
    notificationBarLayout->addWidget(serialPos);

    // Etiquetas para mostrar fecha y hora
    QLabel *dateLabel = new QLabel;
    timeLabel = new QLabel;

    // Establecer formato de fecha y hora actual
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString dateFormat = "dd/MM/yyyy";
    QString timeFormat = "hh:mm:ss";
    dateLabel->setText(currentDateTime.toString(dateFormat));
    dateLabel->setStyleSheet("font-size: 10pt; border: none;");
    timeLabel->setStyleSheet("font-size: 10pt; border: none;");

    // Temporizador
    QTimer *timer = new QTimer(this);

    // Conectar el temporizador al slot updateTime() para actualizar la hora segundo a segundo
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));

    // Establece el intervalo del temporizador en 1000 ms (1 segundo)
    timer->start(1000);

    // Agrega las etiquetas de fecha y hora a la barra de notificaciones
    notificationBarLayout->addWidget(dateLabel);

    notificationBarLayout->addStretch();

    notificationBarLayout->addWidget(timeLabel);

    // Agrega un espacio flexible entre las etiquetas de fecha y hora
    notificationBarLayout->addStretch();

    QLabel *networkIcon = new QLabel;
    QPixmap pixmapNetwork(":/assets/icons/config/interface-essential-wifi-feed.png");
    pixmapNetwork = pixmapNetwork.scaled(QSize(13, 13), Qt::KeepAspectRatio);
    networkIcon->setPixmap(pixmapNetwork);
    networkIcon->setStyleSheet("border: none; margin-top: -1px;");
    notificationBarLayout->addWidget(networkIcon);

    QLabel *chargeIcon = new QLabel;
    QPixmap pixmapCharge(":/assets/icons/notificaciones/charge.png");
    chargeIcon->setPixmap(pixmapCharge);
    chargeIcon->setStyleSheet("border: none;");
    notificationBarLayout->addWidget(chargeIcon);

    /* QWidget *notificationBarContainer = new QWidget; */
    notificationBarContainer = new QWidget(this);
    notificationBarContainer->setLayout(notificationBarLayout);
    notificationBarContainer->setStyleSheet("border: 1px solid grey; border-radius: 8px;");
    notificationBarContainer->setMaximumHeight(28); // Establecer la altura máxima
    notificationBarContainer->setMinimumHeight(28);

    // Establece la política de expansión horizontal para que el contenedor ocupe todo el ancho de la ventana
    notificationBarContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // Agrega el contenedor de la barra de notificaciones al layout principal
    mainLayout->addWidget(notificationBarContainer);

    // Barra de navegación en la fila 2
    QHBoxLayout *navigationBarLayout = new QHBoxLayout;

    navigationBarLayout->addWidget(button1);
    navigationBarLayout->addWidget(button2);
    navigationBarLayout->addWidget(button3);
    navigationBarLayout->addWidget(button4);

    /* QWidget *navigationBarContainer = new QWidget; */
    navigationBarContainer = new QWidget(this);
    navigationBarContainer->setLayout(navigationBarLayout);
    navigationBarContainer->setStyleSheet("border: 2px solid black; border-radius: 4px;");
    mainLayout->addWidget(navigationBarContainer, 2, 0, 1, 1, Qt::AlignBottom);

    // Agregar el stackedWidget al layout principal
    mainLayout->addWidget(stackedWidget, 1, 0, 1, 1, Qt::AlignCenter);

    // Configurar el widget central
    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Validar si el usuario está autenticado para mostrar la barra de navegación y la barra de notificaciones
    if (!isAuthenticated)
    {
        notificationBarContainer->setVisible(false);
        navigationBarContainer->setVisible(false);
    }
}

MainWindow::~MainWindow()
{
    delete loginScreen;
    delete homeScreen;
    delete productScreen;
    delete recargaBilleteraScreen;
    delete recargaMifareScreen;
    delete historyScreen;
    delete stackedWidget;
    delete configScreen;
    delete wifiScreen;
    delete wifiConnectScreen;
    delete saleProgress;
    delete mifareSaleProgress;
    delete saleSuccess;
    delete saleError;
    delete mifareSaleSuccess;
    delete mifareSaleError;
}

void MainWindow::refreshToken()
{

    // Obtener el refreshToken del singleton
    QString refreshToken = SessionManager::instance().getRefreshToken();

    // Crear la solicitud de red para refrescar el token
    QNetworkRequest request(QUrl("https://fleet.nebulae.com.co/auth/realms/FLEET/protocol/openid-connect/token"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Cookie", "KEYCLOAK_LOCALE=es_CO; INGRESSCOOKIE=1718115185.52.580.357024|4fe595e6a021e9a92488ba8bb40d9f57");

    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    connect(networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(handleTokenReply(QNetworkReply *)));

    // Crear los datos para la solicitud
    QByteArray data;
    data.append("grant_type=refresh_token");
    data.append("&scope=openid");
    data.append("&refresh_token=" + refreshToken);
    data.append("&client_id=emi");

    // Enviar la solicitud de red
    networkManager->post(request, data);
}

void MainWindow::handleTokenReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray responseData = reply->readAll();

        // Parsear la respuesta JSON para obtener el nuevo access_token
        QString jwtToken = responseData;

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
    }
    else
    {
        qDebug() << "Error al refrescar el token:" << reply->errorString();
    }
    reply->deleteLater();
}

QVariantMap MainWindow::stringToJson(const QString &jsonString)
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

void MainWindow::showLoginScreen()
{
    if (loginScreen != NULL)
        stackedWidget->setCurrentWidget(loginScreen);
}

void MainWindow::showHomeScreen()
{
    if (homeScreen != NULL)
        stackedWidget->setCurrentWidget(homeScreen);
}

void MainWindow::showProductScreen()
{
    if (productScreen != NULL)
        stackedWidget->setCurrentWidget(productScreen);
}

void MainWindow::showHistoryScreen()
{
    if (historyScreen != NULL)
        stackedWidget->setCurrentWidget(historyScreen);
}

void MainWindow::showRecargaBilleteraScreen()
{
    if (recargaBilleteraScreen != NULL)
        stackedWidget->setCurrentWidget(recargaBilleteraScreen);
}

void MainWindow::showRecargaMifareScreen()
{
    if (recargaMifareScreen != NULL)
        stackedWidget->setCurrentWidget(recargaMifareScreen);
}

void MainWindow::showConfigScreen()
{
    if (configScreen != NULL)
        stackedWidget->setCurrentWidget(configScreen);
}

void MainWindow::setAuthenticated()
{
    isAuthenticated = true;
    stackedWidget->setCurrentWidget(productScreen);
    notificationBarContainer->setVisible(isAuthenticated);
    navigationBarContainer->setVisible(isAuthenticated);

    qDebug() << "Recibiendo desde loginscreen" << "todo ok";
}

void MainWindow::changeToWifiScreen()
{
    if (wifiScreen != NULL)
        stackedWidget->setCurrentWidget(wifiScreen);
}

void MainWindow::changeToWifiConnectScreen()
{
    if (wifiConnectScreen != NULL)
        stackedWidget->setCurrentWidget(wifiConnectScreen);
}

void MainWindow::changeToSaleScreen()
{
    notificationBarContainer->setVisible(false);
    navigationBarContainer->setVisible(false);
    stackedWidget->setCurrentWidget(saleProgress);
    saleProgress->startAnimation();
    qDebug()
        << "Cambiar a saleProgress" << "todo ok";
}

void MainWindow::changeToSaleSuccessScreen()
{
    stackedWidget->setCurrentWidget(saleSuccess);
    qDebug() << "Cambiar a saleSuccess" << "todo ok";
}

void MainWindow::changeToSaleErrorScreen()
{
    stackedWidget->setCurrentWidget(saleError);
    qDebug() << "Cambiar a saleError" << "todo ok";
}

void MainWindow::changeBackToRecargaBilletera()
{
    notificationBarContainer->setVisible(true);
    navigationBarContainer->setVisible(true);
    stackedWidget->setCurrentWidget(recargaBilleteraScreen);
    qDebug() << "Cambiar a RecargaBilletera" << "todo ok";
}

void MainWindow::changeToMifareSaleScreen()
{
    notificationBarContainer->setVisible(false);
    navigationBarContainer->setVisible(false);
    stackedWidget->setCurrentWidget(mifareSaleProgress);
    mifareSaleProgress->startAnimation();
    qDebug() << "Cambiar a mifareSaleProgress" << "todo ok";
}

void MainWindow::changeToMifareSaleSuccessScreen()
{
    stackedWidget->setCurrentWidget(mifareSaleSuccess);
    qDebug() << "Cambiar a mifareSaleSuccess" << "todo ok";
}

void MainWindow::changeToMifareSaleErrorScreen()
{
    stackedWidget->setCurrentWidget(mifareSaleError);
    QString text = SessionManager::instance().getMifareSaleErrorMessage();
    qDebug() << "text" << text;
    mifareSaleError->handleChangeText(text);
    qDebug() << "Cambiar a mifareSaleError" << "todo ok";
}

void MainWindow::changeBackToRecargaMifare()
{
    notificationBarContainer->setVisible(true);
    navigationBarContainer->setVisible(true);
    stackedWidget->setCurrentWidget(recargaMifareScreen);
    recargaMifareScreen->cleanSomeVariables();
    qDebug() << "Cambiar a RecargaMifare" << "todo ok";
}

void MainWindow::setNotAuthenticated()
{
    isAuthenticated = false;
    stackedWidget->setCurrentWidget(loginScreen);
    qDebug() << "Recibiendo desde loginscreen" << "Auth Error";
}
void MainWindow::updateTime()
{
    // Obtener la hora actual en UTC
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // Formatear la hora
    QString timeFormat = "hh:mm:ss";
    QString currentTime = currentDateTime.toString(timeFormat);

    // Actualizar el texto de la etiqueta de tiempo
    timeLabel->setText(currentTime);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QWidget *focusedWidget = QApplication::focusWidget();
    if (focusedWidget && qobject_cast<QLineEdit *>(focusedWidget))
    {
        // Si un QLineEdit tiene el foco, no cambiar de pantalla
        QWidget::keyPressEvent(event);
        return;
    }

    switch (event->key())
    {
    case Qt::Key_F1:
        moveLeft();
        break;
    case Qt::Key_F4:
        moveRight();
        break;
    default:
        QMainWindow::keyPressEvent(event);
        qDebug() << "Tecla presionada:" << QKeySequence(event->key()).toString();
        break;
    }
}

void MainWindow::moveLeft()
{
    // Si estamos en la primera pantalla (homeScreen), no hacemos nada
    if (currentIndex == 0)
        return;

    currentIndex = (currentIndex - 1) % screens.size();
    stackedWidget->setCurrentWidget(screens[currentIndex]);
}

void MainWindow::moveRight()
{
    // Si estamos en la última pantalla (configScreen), no hacemos nada
    if (currentIndex == screens.size() - 1)
        return;

    currentIndex = (currentIndex + 1) % screens.size();
    stackedWidget->setCurrentWidget(screens[currentIndex]);
}
