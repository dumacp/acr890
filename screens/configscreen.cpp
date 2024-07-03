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
