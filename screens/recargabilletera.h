#ifndef RECARGABILLETERA_H
#define RECARGABILLETERA_H

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

class RecargaBilleteraScreen : public QWidget
{
    Q_OBJECT

public:
    RecargaBilleteraScreen(QWidget *parent = 0);
    void rotateWindow();

protected:
    void keyPressEvent(QKeyEvent *event);

signals:
    void showSaleScreen();

public slots:
    void
    handleSubmit();
    void handleTextChanged(const QString &);
    void getCurrentBalance(const QString &);
    void handleNetworkReply(QNetworkReply *reply);
    void executeSale(const QString &);
    QVariant parseJsonValue(const QString &jsonString);
    QVariantList parseJsonArray(const QString &jsonString);
    void updateSaldoLabel(int balance, const QString &response);
    void restoreSaldoLabel();
    int removeCommasAndConvertToInt(const QString &priceString);
    void validateAddressText(const QString &text);
    QString extractNumericValue(const QString &text);
    void emitSaleSuccessToMainWindow();
    void emitSaleErrorToMainWindow();

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
};
//! [class definition]

#endif // RECARGABILLETERA_H
