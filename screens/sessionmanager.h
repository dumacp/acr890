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

    // Get & Set JwtToken
    void setJwtToken(const QString &token) { jwtToken = token; }
    QString getJwtToken() const { return jwtToken; }

    // Get & Set AccessToken
    void setAccessToken(const QString &access) { accessToken = access; }
    QString getAccessToken() const { return accessToken; }

    // Get & Set RefreshToken
    void setRefreshToken(const QString &refresh) { refreshToken = refresh; }
    QString getRefreshToken() const { return refreshToken; }

    // Set Execute Mifare Sale
    void setExecuteMifareSale(const bool &executeMifareTypeSale) { executeMifareSale = executeMifareTypeSale; }
    bool getExecuteMifareSale() const { return executeMifareSale; }

    // Get & Set Mifare Sale ATR
    void setMifareSaleATR(const QString &mifareATR) { mifareSaleATR = mifareATR; }
    QString getMifareSaleATR() const { return mifareSaleATR; }

    // Get & Set Mifare UUID
    void setMifareSaleUUID(const QString &mifareUUID) { mifareSaleUUID = mifareUUID; }
    QString getMifareSaleUUID() const { return mifareSaleUUID; }

    // Get & Set MifareSaleError Mesage
    void setMifareSaleErrorMessage(const QString &errorMessage) { mifareErrorMessage = errorMessage; }
    QString getMifareSaleErrorMessage() const { return mifareErrorMessage; }

    // Get & Set currentUserId
    void setCurrentUserId(const QString &currentUserId) { userId = currentUserId; }
    QString getCurrentUserId() const { return userId; }

    // Get & Set PaymentMediumId in order to execute the mifare sale
    void setPaymentMediumId(const QString &paymentMediumId) { currentPaymentMediumId = paymentMediumId; }
    QString getPaymentMediumId() const { return currentPaymentMediumId; }

    // Get & Set current user document
    void setCurrentUserDocument(const QString &document) { userDocument = document; }
    QString getCurrentUserDocument() const { return userDocument; }

    // Get & Set curretn unit price
    void setCurrentUnitPrice(const int &unitPrice) { currentUnitPrice = unitPrice; }
    int getCurrentUnitPrice() const { return currentUnitPrice; }

    // Get & Set current mifare value to recharge
    void setCurrentMifareUnitPrice(const int &mifareUnitPrice) { currentMifareUnitPrice = mifareUnitPrice; }
    int getCurrentMifareUnitPrice() const { return currentMifareUnitPrice; }

    // Get & Set POS Data
    void setPointOfSaleData(const QByteArray &data) { pointOfSaleData = data; }
    QByteArray getPointOfSaleData() const { return pointOfSaleData; }

    // Get & Set POS ID
    void setPosId(const QString &posId) { currentPosId = posId; }
    QString getPosId() const { return currentPosId; }

    // Get & Set current access token
    void setCurrentAccessToken(const QString &accessToken) { currentAccessToken = accessToken; }
    QString getCurrentAccessToken() const { return currentAccessToken; }

    // Get & Set Message to print
    void setMessageToPrint(const QString &message) { messageToPrint = message; }
    QString getMessageToPrint() const { return messageToPrint; }

private:
    SessionManager() {}
    QString jwtToken;
    QString accessToken;
    QString refreshToken;
    QString userId;
    QString userDocument;
    QString mifareSaleATR;
    QString mifareSaleUUID;
    QString currentPaymentMediumId;
    int currentUnitPrice;
    int currentMifareUnitPrice;
    QByteArray pointOfSaleData;
    QString currentAccessToken;
    QString currentPosId;
    QString messageToPrint;
    QString mifareErrorMessage;
    bool executeMifareSale;

    // Disable copy and assignment
    SessionManager(const SessionManager &);
    void operator=(const SessionManager &);
};

#endif // SESSIONMANAGER_H
