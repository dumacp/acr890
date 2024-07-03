#ifndef MIFARESALEPROGRESS_H
#define MIFARESALEPROGRESS_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QVector>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTimer>
#include <QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QVariant>
#include <QVariantList>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// standard
#include <stdint-gcc.h>
#include <stdint.h>
#include <vector>

#include "../../../smartCard/MifareClassic.h"
#include "../../../smartCard/AcsHelper.h"
#include "../../../smartCard/AcsReader.h"
#include "../../../smartCard/AcsException.h"

class MifareSaleProgress : public QWidget
{
    Q_OBJECT

public:
    MifareSaleProgress(QWidget *parent = 0);
    void startAnimation();
    ~MifareSaleProgress();

signals:
    void progressMifareDoneSuccess();
    void progressMifareDoneError();

private slots:
    void updateIcon();
    void handleCompleteTimer();
    void handlePostNetworkReplySale(QNetworkReply *reply);
    void processJson(const QVariant &json);
    void handleApiResponse(const QString &response);

    // Parse Data
    QVariant parseJsonValue(const QString &jsonString);
    QVariantList parseJsonArray(const QString &jsonString);
    QVariantMap stringToJson(const QString &jsonString);
    QVariantMap parseJsonObject(const QString &jsonString);
    QVariantMap parseJson(const QString &jsonString);

    // Card
    void piccReader();
    void readWriteCard(const QString &atr, const QString &uuid);
    void handlePostNetworkReply(QNetworkReply *reply);
    void readWriteCardStepZero(std::vector<ParsedApduResponse> responseApdus);
    void handlePostNetworkReplyZero(QNetworkReply *reply);

    // Printer
    void runPrinter(const QString &response);

private:
    QLabel *iconLabel;
    QLabel *textLabel;
    QVector<QPixmap> icons;
    int currentIndex;
    QTimer *timer;
    QTimer *completeTimer;
    QLabel *additionalTextLabel;
    QLabel *additionalIconLabel;
    QPushButton *button1;
    QPushButton *button2;
    bool completeTimerStarted;
    bool animationStarted;

    // Clean this later
    QString generarResponseApdus(const std::vector<ParsedApduResponse> responseApdus);

    QString pointOfSaleDataString;
    QVariantMap pointOfSaleData;
    QString posId;
    QString posData;
    QString productId;
    QString jwtToken;
    QString userId;
    QString userDocument;
    QString currentUnitPrice;

    QString cardData;
    QString cardDataSecond;
    QString atrNumberConfig;
    QString uuidConfig;
    QString stepNumber;
    QString sessionIdConfig;
    std::vector<ParsedApduResponse> responseApdus;

    QSignalMapper *signalMapper;

    QString userName;
    QString payId;
    QString endUserFullname;
    QString endUserId;
    QString endUserDocument;
    QString currentBalance;
    int balance;
    QString modifyingText;
    QString message;

    void PrintPage(const char *companyName, const char *tipoServicio, const char *sampleText, const char *dateTime);
};

#endif // MIFARESALEPROGRESS_H
