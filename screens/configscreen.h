#ifndef CONFIGSCREEN_H
#define CONFIGSCREEN_H

#include <QWidget>
#include <QList>
#include <QStackedWidget>

// Led test
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

// standard
#include <stdint-gcc.h>
#include <stdint.h>
#include <vector>

// Net
#include <QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include "../smartCard/MifareClassic.h"
#include "../smartCard/AcsHelper.h"
#include "../smartCard/AcsReader.h"
#include "../smartCard/AcsException.h"

//! [class definition]
class ConfigScreen : public QWidget
{
    Q_OBJECT

public:
    ConfigScreen(QWidget *parent = 0);
    void rotateWindow();

public slots:
    void runLed();
    void turnOffLed(); // Nuevo slot para apagar el LED
    void piccReader();
    void handlePostNetworkReply(QNetworkReply *reply);
    void handlePostNetworkReplyZero(QNetworkReply *reply, const QString &atrPos, const QString &uuidPos);
    void readWriteCard(const QString &atr, const QString &uuid);
    void readWriteCardStepZero(const QString &atr, const QString &uuid, const QString &sessionId);

    // Format Data
    QVariant parseJsonValue(const QString &jsonString);
    QVariantMap parseJsonObject(const QString &jsonString);
    QVariantList parseJsonArray(const QString &jsonString);
    void printResponseApdus(const std::vector<ParsedApduResponse> &responseApdus);
    QString bytesToHexString(const std::vector<uint8_t> &bytes);
    QString generarResponseApdus(const std::vector<ParsedApduResponse> &responseApdus);

private:
    MifareClassic cCard_;
    QString cardData;
    QString atr;
    QString uuid;
    QString stepNumber;
    QString sessionId;
    std::vector<ParsedApduResponse> responseApdus;
};
//! [class definition]

#endif // CONFIGSCREEN_H
