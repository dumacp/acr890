#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QWidget>
#include <QList>
#include <QKeyEvent>
#include <QStackedWidget>
#include <QNetworkRequest>
#include <QtNetwork/QNetworkReply>

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QTextEdit;
QT_END_NAMESPACE

//! [class definition]

class LoginScreen : public QWidget
{
    Q_OBJECT

public:
    LoginScreen(QWidget *parentWidget = 0);
    void rotateWindow();

signals:
    void loginSuccessful();
    void submitClicked();
    void authFailed();

public slots:
    void handleSubmit();
    void handleTextChanged(const QString &);
    void handleNetworkReply();
    void handleSecondaryNetworkReply(QNetworkReply *reply);
    void emitLoginSuccessToMainWindow();
    void emitLoginErrorToMainWindow();

private:
    QWidget *notificationBarContainer;
    QLineEdit *nameLine;
    QLineEdit *addressText;
    QLabel *resultLabel;
    QString jwtToken;

    QVariantMap stringToJson(const QString &jsonString);
};
//! [class definition]

#endif
