#include "mifaresaleerror.h"
#include "../../sessionmanager.h"

#include <QFont>

MifareSaleError::MifareSaleError(QWidget *parent)
    : QWidget(parent),
      additionalTextLabel(new QLabel("Intenta leer la tarjeta nuevamente", this)) // Inicialización del QLabel
{
    // Inicializa el icono
    QPixmap icon(":/assets/icons/sale/interface-essential-skull-1.png"); // Actualiza el icono a uno de error

    // Crear un layout vertical para organizar los elementos
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0); // Eliminar márgenes
    mainLayout->setSpacing(10);                 // Ajustar el espacio entre los elementos

    // Configura el QLabel para mostrar el texto
    textLabel = new QLabel("Ups, algo salio mal", this);
    textLabel->setAlignment(Qt::AlignCenter);
    QFont font("Arial", 14, QFont::Bold);
    textLabel->setFont(font);
    mainLayout->addWidget(textLabel, 0, Qt::AlignCenter);

    // Configura un layout vertical para el icono y el texto adicional
    QVBoxLayout *iconTextLayout = new QVBoxLayout();

    // Agrega el icono
    iconLabel = new QLabel(this);
    iconLabel->setPixmap(icon);
    iconTextLayout->addWidget(iconLabel, 0, Qt::AlignCenter);

    // Agrega el texto adicional debajo del icono
    additionalTextLabel->setAlignment(Qt::AlignCenter);
    iconTextLayout->addWidget(additionalTextLabel, 0, Qt::AlignCenter);

    // Agrega el layout de icono y texto adicional al layout principal
    mainLayout->addLayout(iconTextLayout);

    // Configura los botones

    QPushButton *buttonTry = new QPushButton("Intenta nuevamente", this);
    QPushButton *buttonBack = new QPushButton("Salir", this);

    connect(buttonBack, SIGNAL(clicked()), this, SLOT(backToMifareScreenSlot()));
    connect(buttonTry, SIGNAL(clicked()), this, SLOT(backToMifareSaleProgressSlot()));

    // Establecer el tamaño fijo de los botones
    buttonTry->setFixedWidth(222);
    buttonTry->setFixedHeight(50);
    buttonBack->setFixedWidth(222);
    buttonBack->setFixedHeight(50);

    // Establecer el estilo
    QString buttonStyle = "QPushButton {"
                          "    background-color: white;"
                          "    border: 1px solid black;"
                          "    border-radius: 4px;"
                          "    padding: 5px;"
                          "}"
                          "QPushButton:hover {"
                          "    background-color: lightgray;"
                          "}"
                          "QPushButton:pressed {"
                          "    background-color: gray;"
                          "}";
    buttonTry->setStyleSheet(buttonStyle);
    buttonBack->setStyleSheet(buttonStyle);

    // Agrega los botones al layout principal
    mainLayout->addWidget(buttonTry);
    mainLayout->addWidget(buttonBack);

    // Configura el layout principal como el diseño del widget
    setLayout(mainLayout);
}

void MifareSaleError::handleChangeText(const QString &text)
{
    additionalTextLabel->setText(text);
}

void MifareSaleError::backToMifareScreenSlot()
{
    emit backToMifareScreen();
}

void MifareSaleError::backToMifareSaleProgressSlot()
{
    // SessionManager::instance().setExecuteMifareSale(false);
    emit backToMifareSaleProgressScreen();
}
