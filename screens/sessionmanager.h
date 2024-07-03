#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <QString>

class SessionManager
{
public:
    static SessionManager &instance()
    {
        static SessionManager instance;
        return instance;
    }

    void setJwtToken(const QString &token) { jwtToken = token; }
    QString getJwtToken() const { return jwtToken; }

    void setCurrentUserId(const QString &id) { userId = id; }
    QString getCurrentUserId() const { return userId; }

    void setPaymentMediumId(const QString &paymentMediumId) { currentPaymentMediumId = paymentMediumId; }
    QString getPaymentMediumId() const { return currentPaymentMediumId; }

    void setCurrentUserDocument(const QString &document) { userDocument = document; }
    QString getCurrentUserDocument() const { return userDocument; }

    void setCurrentUnitPrice(const int &unitPrice) { currentUnitPrice = unitPrice; }
    int getCurrentUnitPrice() const { return currentUnitPrice; }

    void setCurrentMifareUnitPrice(const int &mifareUnitPrice) { currentMifareUnitPrice = mifareUnitPrice; }
    int getCurrentMifareUnitPrice() const { return currentMifareUnitPrice; }

    void setPointOfSaleData(const QByteArray &data) { pointOfSaleData = data; }
    QByteArray getPointOfSaleData() const { return pointOfSaleData; }

    void setPosId(const QString &posId) { currentPosId = posId; }
    QString getPosId() const { return currentPosId; }

    void setCurrentAccessToken(const QString &accessToken) { currentAccessToken = accessToken; }
    QString getCurrentAccessToken() const { return currentAccessToken; }

    void setMessageToPrint(const QString &message) { messageToPrint = message; }
    QString getMessageToPrint() const { return messageToPrint; }

private:
    SessionManager() {}
    QString jwtToken;
    QString userId;
    QString userDocument;
    QString currentPaymentMediumId;
    int currentUnitPrice;
    int currentMifareUnitPrice;
    QByteArray pointOfSaleData;
    QString currentAccessToken;
    QString currentPosId;
    QString messageToPrint;

    // Disable copy and assignment
    SessionManager(const SessionManager &);
    void operator=(const SessionManager &);
};

#endif // SESSIONMANAGER_H
