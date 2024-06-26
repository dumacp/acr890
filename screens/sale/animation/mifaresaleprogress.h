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

class MifareSaleProgress : public QWidget
{
    Q_OBJECT

public:
    MifareSaleProgress(QWidget *parent = 0);
    void startAnimation();

signals:
    void progressDoneSuccess();
    void progressDoneError();

private slots:
    void updateIcon();
    void handleCompleteTimer();
    void handlePostNetworkReply(QNetworkReply *reply);
    void processJson(const QVariant &json);
    void handleApiResponse(const QString &response);
    QVariant parseJsonValue(const QString &jsonString);
    QVariantList parseJsonArray(const QString &jsonString);

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

    QVariantMap stringToJson(const QString &jsonString);
    QVariantMap parseJsonObject(const QString &jsonString);

    QVariantMap parseJson(const QString &jsonString);

    QString pointOfSaleDataString;
    QVariantMap pointOfSaleData;
    QString posId;
    QString posData;
    QString productId;
    QString jwtToken;
    QString userId;
    QString userDocument;
    QString currentUnitPrice;

    void PrintPage(const char *companyName, const char *tipoServicio, const char *sampleText, const char *dateTime);
};

#endif // MIFARESALEPROGRESS_H
