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

// En el constructor de WifiSetup:
WifiScreen::WifiScreen(QWidget *parent)
    : QWidget(parent)
{
    // Crear una lista de registros de venta de ejemplo (puedes reemplazarlo con tu propia lista)
    QList<QString> salesHistory;
    salesHistory.append("ESSID PRUEBA");
    salesHistory.append("ESSID 2");
    salesHistory.append("ESSID 3");
    salesHistory.append("ESSID 3");
    salesHistory.append("ESSID 3");
    salesHistory.append("ESSID 3");
    salesHistory.append("ESSID 3");
    salesHistory.append("ESSID 3");
    salesHistory.append("ESSID 3");
    salesHistory.append("ESSID 3");
    salesHistory.append("ESSID 3");
    salesHistory.append("ESSID 3");
    salesHistory.append("ESSID 3");
    salesHistory.append("ESSID 3");
    salesHistory.append("ESSID 3");
    salesHistory.append("ESSID 3");
    salesHistory.append("ESSID 3");

    // Establecer el layout principal
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0); // Eliminar márgenes

    // Agregar título
    QLabel *titleLabel = new QLabel("Wifi Setup");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFont(QFont("Arial", 16, QFont::Bold));
    mainLayout->addWidget(titleLabel);

    // Mostrar el historial de ventas en la pantalla
    displaySalesHistory(salesHistory);
}

// Dentro de WifiSetup:
void WifiScreen::displaySalesHistory(const QList<QString> &salesHistory)
{
    salesTable = new QTableWidget(salesHistory.size(), 1); // 1 columna para ESSID

    // Manejar evento doble click
    connect(salesTable, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(handleCellDoubleClicked(int, int)));

    // Encabezados de columna
    QStringList headers;
    headers << "ESSID";
    salesTable->setHorizontalHeaderLabels(headers);

    // Insertar registros en la tabla
    for (int row = 0; row < salesHistory.size(); ++row)
    {
        const QString &serviceType = salesHistory.at(row);
        QTableWidgetItem *item = new QTableWidgetItem(serviceType);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable); // Hacer la celda no editable
        salesTable->setItem(row, 0, item);
    }

    // Ajustar el tamaño de la columna para que ocupe todo el ancho disponible
    salesTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    // Aplicar estilo a los encabezados de columna
    for (int i = 0; i < salesTable->columnCount(); ++i)
    {
        salesTable->horizontalHeaderItem(i)->setBackground(Qt::white);
        salesTable->horizontalHeaderItem(i)->setForeground(Qt::black);
    }

    // Agregar la tabla al layout principal
    mainLayout->addWidget(salesTable); // Agregar la tabla al layout principal
}

void WifiScreen::handleCellDoubleClicked(int row, int column)
{
    if (column == 0) // Verifica que el doble clic haya sido en la columna "ESSID"
    {
        QTableWidgetItem *item = salesTable->item(row, column);
        if (item)
        {
            QString text = item->text();
            qDebug() << "Doble clic en ESSID:" << text;

            // Enviar ESSID al singleton
            SessionManager::instance().setCurrentESSID(text);

            // Ir a WifiConnectScreen
            emit changeToWifiConnect();
        }
    }
}