#ifndef RECARGAMIFARE_H
#define RECARGAMIFARE_H

#include <QWidget>
#include <QList>
#include <QStackedWidget>
#include <QKeyEvent>
#include <QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QStringList>
#include <QVariant>
#include <QVariantList>
#include "screens/homescreen.h"
#include "screens/productscreen.h"

// standard
#include <stdint-gcc.h>
#include <stdint.h>
#include <vector>

#include "../smartCard/MifareClassic.h"
#include "../smartCard/AcsHelper.h"
#include "../smartCard/AcsReader.h"
#include "../smartCard/AcsException.h"

//! [class definition]

class RecargaMifareScreen : public QWidget
{
    Q_OBJECT

public:
    RecargaMifareScreen(QWidget *parent = 0);
    void rotateWindow();
    ~RecargaMifareScreen();

protected:
    void keyPressEvent(QKeyEvent *event);

signals:
    void showMifareSaleScreen();

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

public slots:
    void
    handleSubmit();
    void handleTextChanged(const QString &);
    void executeSale(const QString &);
    QVariant parseJsonValue(const QString &jsonString);
    void updateSaldoLabel(int balance, const QString &response);
    void restoreSaldoLabel();
    int removeCommasAndConvertToInt(const QString &priceString);
    void validateAddressText(const QString &text);
    QString extractNumericValue(const QString &text);
    void emitMifareSaleSuccessToMainWindow();
    void emitMifareSaleErrorToMainWindow();
    void piccReader();

    // Card
    void checkForCard();
    void readWriteCard(const QString &atr, const QString &uuid);
    void handlePostNetworkReply(QNetworkReply *reply);
    void readWriteCardStepZero(std::vector<ParsedApduResponse> responseApdus);
    void handlePostNetworkReplyZero(QNetworkReply *reply);

    QVariantMap parseJsonObject(const QString &jsonString);
    QVariantList parseJsonArray(const QString &jsonString);
    QString generarResponseApdus(const std::vector<ParsedApduResponse> responseApdus);
    QVariantMap stringToJson(const QString &jsonString);

private:
    // Card
    QString cardData;
    QString cardDataSecond;
    QString atrNumberConfig;
    QString uuidConfig;
    QString stepNumber;
    QString sessionIdConfig;
    std::vector<ParsedApduResponse> responseApdus;

    QSignalMapper *signalMapper;

    QTimer *timer;
    QLineEdit *addressText;
    QLabel *infoText;
    QLabel *saldoLabel;
    QLabel *valorLabel;
    QLabel *saldoNuevoLabel;
    QLabel *valorNuevoLabel;
    QLabel *resultLabel;
    QString jwtToken;
    QString posId;
    QString userName;
    QString userId;
    QString userDocument;
    QString payId;
    QString endUserFullname;
    QString endUserId;
    QString endUserDocument;
    QString currentBalance;
    QString modifyingText;
};
//! [class definition]

#endif // RECARGAMIFARE_H
