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

    /* void setPosData(const QString &data) { posData = data; }
    QString getPosData() const { return posData; } */

    void setCurrentUserId(const QString &id) { userId = id; }
    QString getCurrentUserId() const { return userId; }

    void setCurrentUserDocument(const QString &document) { userDocument = document; }
    QString getCurrentUserDocument() const { return userDocument; }

    void setCurrentUnitPrice(const int &unitPrice) { currentUnitPrice = unitPrice; }
    int getCurrentUnitPrice() const { return currentUnitPrice; }

    void setPointOfSaleData(const QByteArray &data) { pointOfSaleData = data; }
    QByteArray getPointOfSaleData() const { return pointOfSaleData; }

    void setPosId(const QString &posId) { currentPosId = posId; }
    QString getPosId() const { return currentPosId; }

    void setCurrentAccessToken(const QString &accessToken) { currentAccessToken = accessToken; }
    QString getCurrentAccessToken() const { return currentAccessToken; }

private:
    SessionManager() {}
    QString jwtToken;
    QString userId;
    QString userDocument;
    int currentUnitPrice;
    QByteArray pointOfSaleData;
    QString currentAccessToken;
    QString currentPosId;

    // Disable copy and assignment
    SessionManager(const SessionManager &);
    void operator=(const SessionManager &);
};

#endif // SESSIONMANAGER_H
