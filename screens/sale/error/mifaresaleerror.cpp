#include "mifaresaleerror.h"
#include <QFont>

MifareSaleError::MifareSaleError(QWidget *parent)
    : QWidget(parent)
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
    QLabel *additionalTextLabel = new QLabel("Intenta nuevamente mas tarde", this);
    additionalTextLabel->setAlignment(Qt::AlignCenter);
    iconTextLayout->addWidget(additionalTextLabel, 0, Qt::AlignCenter);

    // Agrega el layout de icono y texto adicional al layout principal
    mainLayout->addLayout(iconTextLayout);

    // Configura los botones
    QPushButton *button2 = new QPushButton("Salir", this);

    // Conectar la señal 'clicked()' del boton salir al slot 'backToMifareScreenSlot' para regresar a RecargaMifareScreen
    connect(button2, SIGNAL(clicked()), this, SLOT(backToMifareScreenSlot()));

    // Establecer el tamaño fijo de los botones
    button2->setFixedWidth(222);
    button2->setFixedHeight(50);

    // Establecer el estilo de los botones
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
    button2->setStyleSheet(buttonStyle);

    // Agrega los botones al layout principal
    mainLayout->addWidget(button2, 0, Qt::AlignCenter);

    // Configura el layout principal como el diseño del widget
    setLayout(mainLayout);
}

void MifareSaleError::backToMifareScreenSlot()
{
    emit backToMifareScreen();
}