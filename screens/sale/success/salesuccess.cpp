#include "salesuccess.h"
#include <QFont>

SaleSuccess::SaleSuccess(QWidget *parent)
    : QWidget(parent)
{
    QPixmap icon(":/assets/icons/sale/money-payments-accounting-bill-money-2.png"); // Actualiza el icono a uno de error

    // Crear un layout vertical para organizar los elementos
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0); // Eliminar márgenes
    mainLayout->setSpacing(10);                 // Ajustar el espacio entre los elementos

    // Configura el QLabel para mostrar el texto
    textLabel = new QLabel("Venta Realizada!!", this);
    textLabel->setAlignment(Qt::AlignCenter);
    textLabel->setStyleSheet("QLabel { font-size: 14px; font-weight: bold; }");
    mainLayout->addWidget(textLabel, 0, Qt::AlignCenter);

    // Configura un layout horizontal para el icono
    QHBoxLayout *iconLayout = new QHBoxLayout();
    iconLayout->setContentsMargins(0, 0, 0, 0); // Eliminar márgenes
    iconLayout->setSpacing(10);                 // Ajustar el espacio entre los elementos

    // Agrega el icono
    iconLabel = new QLabel(this);
    iconLabel->setPixmap(icon);
    iconLayout->addWidget(iconLabel, 0, Qt::AlignCenter);

    // Agrega el layout de icono al layout principal
    mainLayout->addLayout(iconLayout);

    // Configura los botones
    QPushButton *button1 = new QPushButton("Imprimir copia", this);
    QPushButton *button2 = new QPushButton("Salir", this);

    // Conectar la señal 'clicked()' del boton "Imprimir copia" al slot 'printPage' para imprimir una copía de la factura
    // connect(button1, SIGNAL(clicked()), this, SLOT(printCopyPage()));

    // Conectar la señal 'clicked()' del boton salir al slot 'backToBilleteraScreenSlot' para regresar a RecargaBilleteraScreen
    connect(button2, SIGNAL(clicked()), this, SLOT(backToBilleteraScreenSlot()));

    // Establecer el tamaño fijo de los botones
    button1->setFixedWidth(222);
    button1->setFixedHeight(50);
    button2->setFixedWidth(222);
    button2->setFixedHeight(50);

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
    button1->setStyleSheet(buttonStyle);
    button2->setStyleSheet(buttonStyle);

    // Agrega los botones al layout principal
    mainLayout->addWidget(button1);
    mainLayout->addWidget(button2);

    // Configura el layout principal como el diseño del widget
    setLayout(mainLayout);
}

/* void SaleSuccess::printCopyPage() {

} */

void SaleSuccess::backToBilleteraScreenSlot()
{
    emit backToBilleteraScreen();
}