#include <QtGui>
#include "wifisetup.h"
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QFile>
#include <QFileInfo>
#include <QNetworkRequest>
#include <QStringList>
#include <QTimer>
#include <QUrl>
#include <QTableWidgetItem>
#include <stdio.h>
#include <QHeaderView>
#include "sessionmanager.h"
#include <QShowEvent>

extern "C"
{
#include <acs_api.h>
#include <acs_errno.h>
#include <acs_ioctl.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "wpa_ctrl.h"
}

struct wpa_ctrl *ctrl;
int network_id;
char ssid_buf[2048];
unsigned int ssid_len;
char ssid_cmd[128];
int wifi_close_flag;
int no_driver_flag;

// En el constructor de WifiSetup:
WifiScreen::WifiScreen(QWidget *parent)
    : QWidget(parent)
{
    // Establecer el layout principal
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0); // Eliminar márgenes

    // Agregar título
    QLabel *titleLabel = new QLabel("Wifi Setup");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFont(QFont("Arial", 16, QFont::Bold));
    mainLayout->addWidget(titleLabel);

    // Crear la tabla una sola vez
    salesTable = new QTableWidget(0, 1); // Inicialmente sin filas, 1 columna para ESSID
    mainLayout->addWidget(salesTable);   // Agregar la tabla al layout principal

    // Configurar la tabla
    salesTable->setHorizontalHeaderLabels(QStringList() << "SSID");
    salesTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch); // Ajustar ancho de la columna

    // Conectar señal de doble clic
    connect(salesTable, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(handleCellDoubleClicked(int, int)));
}

WifiScreen::~WifiScreen()
{
}

void WifiScreen::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event); // Llama al showEvent de la clase base si es necesario

    // Aquí ejecuta la función scanResults
    scanResults();
}

// Mostrar listado de redes encontradas
void WifiScreen::displaySalesHistory(const QList<QString> &salesHistory)
{
    // Limpiar contenido existente de la tabla
    salesTable->setRowCount(0);

    // Insertar registros en la tabla
    for (int row = 0; row < salesHistory.size(); ++row)
    {
        const QString &serviceType = salesHistory.at(row);
        QTableWidgetItem *item = new QTableWidgetItem(serviceType);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable); // Hacer la celda no editable
        salesTable->insertRow(row);
        salesTable->setItem(row, 0, item);
    }
}

// Seleccionar red y almacenar ESSID en el singleton
void WifiScreen::handleCellDoubleClicked(int row, int column)
{
    if (column == 0) // Verifica que el doble clic haya sido en la columna "ESSID"
    {
        QTableWidgetItem *item = salesTable->item(row, column);
        if (item)
        {
            QString text = item->text();
            qDebug() << "Doble clic en SSID:" << text;

            // Enviar ESSID al singleton
            SessionManager::instance().setCurrentSSID(text);

            // Ir a WifiConnectScreen
            emit changeToWifiConnect();
        }
    }
}

void WifiScreen::scanResults()
{
    QProcess process;
    QStringList arguments;

    // Realizar el escaneo con wpa_cli
    process.start("wpa_cli scan");
    process.waitForFinished();

    // Obtener los resultados del escaneo
    process.start("wpa_cli scan_results");
    process.waitForFinished();

    QString output(process.readAllStandardOutput());
    // qDebug() << output;

    // Procesar los resultados del escaneo y actualizar la tabla
    QList<QString> scanResultsList;
    QStringList lines = output.split("\n");

    foreach (const QString &line, lines)
    {
        QStringList parts = line.split(QRegExp("\\s+"), QString::SkipEmptyParts); // Dividir por espacios en blanco y omitir partes vacías
        if (parts.size() > 4)                                                     // Asegurarse de que hay suficientes partes en la línea
        {
            QString ssid = parts.last().trimmed(); // Tomar la última parte y eliminar los espacios en blanco
            if (ssid != "ssid")
            {
                qDebug() << "SSID:" << ssid;
                scanResultsList.append(ssid); // Puedes decidir qué información añadir a la lista
            }
        }
    }

    // Actualizar la tabla con los resultados del escaneo
    displaySalesHistory(scanResultsList);
}