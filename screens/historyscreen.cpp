#include <QtGui>
#include "historyscreen.h"
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QFile>
#include <QFileInfo>
#include <QNetworkRequest>
#include <QStringList>
#include <QTimer>
#include <QUrl>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <stdio.h>
#include <QHeaderView>

// En el constructor de HistoryScreen:
HistoryScreen::HistoryScreen(QWidget *parent)
    : QWidget(parent)
{

    // Crear una lista de registros de venta de ejemplo (puedes reemplazarlo con tu propia lista)
    QList<SaleRecord> salesHistory;
    salesHistory.append(SaleRecord("Recarga Billetera", QDate(2024, 5, 15), QTime(10, 30), "Usuario1", 15000));
    salesHistory.append(SaleRecord("Recarga Billetera", QDate(2024, 5, 16), QTime(12, 45), "Usuario2", 20000));
    salesHistory.append(SaleRecord("Recarga Billetera", QDate(2024, 5, 17), QTime(14, 0), "Usuario3", 18000));

    // Establecer el layout principal
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0); // Eliminar márgenes

    // Agregar título
    QLabel *titleLabel = new QLabel("Historial de ventas");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFont(QFont("Arial", 16, QFont::Bold));
    mainLayout->addWidget(titleLabel);

    // Mostrar el historial de ventas en la pantalla
    displaySalesHistory(salesHistory);
}

// Dentro de displaySalesHistory:
void HistoryScreen::displaySalesHistory(const QList<SaleRecord> &salesHistory)
{
    QTableWidget *salesTable = new QTableWidget(salesHistory.size(), 5); // 5 columnas para Tipo de Servicio, Fecha, Hora, Usuario y Valor

    // Encabezados de columna
    QStringList headers;
    headers << "Servicio" << "Fecha" << "Hora" << "Usuario" << "Valor";
    salesTable->setHorizontalHeaderLabels(headers);

    // Insertar registros en la tabla
    for (int row = 0; row < salesHistory.size(); ++row)
    {
        const SaleRecord &record = salesHistory.at(row);
        salesTable->setItem(row, 0, new QTableWidgetItem(record.serviceType));
        salesTable->setItem(row, 1, new QTableWidgetItem(record.date.toString(Qt::ISODate)));
        salesTable->setItem(row, 2, new QTableWidgetItem(record.time.toString(Qt::ISODate)));
        salesTable->setItem(row, 3, new QTableWidgetItem(record.user));

        // QTableWidgetItem *valueItem = new QTableWidgetItem(QString::number(formatNumber(record.value)));
        QTableWidgetItem *valueItem = new QTableWidgetItem(formatNumber(record.value));
        valueItem->setBackground(Qt::white);
        valueItem->setForeground(Qt::black);
        valueItem->setFlags(valueItem->flags() & ~Qt::ItemIsEditable); // Hacer la celda de valor no editable
        salesTable->setItem(row, 4, valueItem);
    }

    // Aplicar estilo a los encabezados de columna
    for (int i = 0; i < salesTable->columnCount(); ++i)
    {
        salesTable->horizontalHeaderItem(i)->setBackground(Qt::white);
        salesTable->horizontalHeaderItem(i)->setForeground(Qt::black);
    }

    // Agregar la tabla al layout principal
    mainLayout->addWidget(salesTable); // Agregar la tabla al layout principal
}

QString HistoryScreen::formatNumber(int number)
{
    // Formatear el número con comas para los miles y agregar el sufijo " COP"
    QString formattedNumber = formatNumberWithCommas(number) + " COP";

    return formattedNumber;
}

QString HistoryScreen::formatNumberWithCommas(int number)
{
    // Formatear el número con comas para los miles
    QString formattedNumber = QString::number(number);
    int commaPos = formattedNumber.length() - 3;
    while (commaPos > 0)
    {
        formattedNumber.insert(commaPos, ',');
        commaPos -= 3;
    }
    return formattedNumber;
}