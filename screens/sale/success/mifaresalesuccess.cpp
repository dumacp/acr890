#include "mifaresalesuccess.h"
#include <QFont>
#include <QDebug>
#include "../../sessionmanager.h"

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

MifareSaleSuccess::MifareSaleSuccess(QWidget *parent)
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

    // Conectar la señal 'clicked()' del boton salir al slot 'backToBilleteraScreenSlot' para regresar a RecargaBilleteraScreen
    connect(button2, SIGNAL(clicked()), this, SLOT(backToMifareScreenSlot()));

    connect(button1, SIGNAL(clicked()), this, SLOT(runPrinter()));

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

void MifareSaleSuccess::backToMifareScreenSlot()
{
    emit backToMifareScreen();
}

void MifareSaleSuccess::runPrinter()
{
    int nRet;

    nRet = printer_open();
    if (nRet < 0)
    {
        qDebug() << "ACR890_Printer_Open error" << nRet;
        return;
    }

    QString response = SessionManager::instance().getMessageToPrint();

    // Imprimir una sola vez
    PrintPage("NebulaE", "Recarga Mifare", response.toUtf8().constData(), "2024/03/19 11:42:44");

    // Cerrar la impresora
    printer_close();
}

void MifareSaleSuccess::PrintPage(const char *companyName, const char *tipoServicio, const char *sampleText, const char *dateTime)
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
