#ifndef WIFICONNECTSCREEN_H
#define WIFICONNECTSCREEN_H

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
#include "screens/recargabilletera.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QTextEdit;
QT_END_NAMESPACE

//! [class definition]

class WifiConnectScreen : public QWidget
{
    Q_OBJECT

public:
    WifiConnectScreen(QWidget *parent = 0);
    void rotateWindow();

protected:
    void keyPressEvent(QKeyEvent *event);
    void showEvent(QShowEvent *event);

signals:
    void showSaleScreen();

public slots:
    void
    handleSubmit();
    void handleTextChanged(const QString &);
    void getCurrentBalance(const QString &);
    void handleNetworkReply(QNetworkReply *reply);
    QVariant parseJsonValue(const QString &jsonString);
    QVariantList parseJsonArray(const QString &jsonString);
    void updateSaldoLabel(int balance, const QString &response);
    void restoreSaldoLabel();
    int removeCommasAndConvertToInt(const QString &priceString);
    QString extractNumericValue(const QString &text);
    void updateWpaSupplicant();

    void setPhonewordsMode(bool mode);
    void handleKeyPress(int key);

private:
    QLineEdit *nameLine;
    QLineEdit *addressText;
    QLabel *infoText;
    QLabel *saldoLabel;
    QLabel *valorLabel;
    QLabel *saldoNuevoLabel;
    QLabel *valorNuevoLabel;
    QLabel *resultLabel;
    QString jwtToken;
    QString userName;
    QString userId;
    QString userDocument;
    QString currentBalance;
    QString modifyingText;

    QVariantMap stringToJson(const QString &jsonString);
    QVariantMap parseJsonObject(const QString &jsonString);

    // Keypad handler
    QString convertToPhoneword(int key);
    QString convertToNumeric(int key);

    bool phonewordsMode; // Bandera para el modo phonewords
    QString currentText;
    QMap<int, QString> keyMap;
};
//! [class definition]

#endif // WIFICONNECTSCREEN_H
