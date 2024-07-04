#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QKeyEvent>

// Screens
// #include "addressbook.h"
#include "screens/loginscreen.h"
#include "screens/dialog/dialog.h"
#include "screens/homescreen.h"
#include "screens/productscreen.h"
#include "screens/recargabilletera.h"
#include "screens/recargamifare.h"
#include "screens/sale/animation/saleprogress.h"
#include "screens/sale/animation/mifaresaleprogress.h"
#include "screens/sale/success/salesuccess.h"
#include "screens/sale/success/mifaresalesuccess.h"
#include "screens/sale/error/saleerror.h"
#include "screens/sale/error/mifaresaleerror.h"
#include "screens/historyscreen.h"
#include "screens/configscreen.h"
#include "screens/wifisetup.h"
#include "screens/wificonnect.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    QWidget *notificationBarContainer;
    QWidget *navigationBarContainer;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QPushButton *button4;
    QStackedWidget *stackedWidget;
    LoginScreen *loginScreen;
    HomeScreen *homeScreen;
    ResponseDialog *responseDialog;
    ProductScreen *productScreen;
    RecargaBilleteraScreen *recargaBilleteraScreen;
    RecargaMifareScreen *recargaMifareScreen;
    SaleProgress *saleProgress;
    SaleSuccess *saleSuccess;
    SaleError *saleError;
    MifareSaleProgress *mifareSaleProgress;
    MifareSaleSuccess *mifareSaleSuccess;
    MifareSaleError *mifareSaleError;
    ConfigScreen *configScreen;
    WifiScreen *wifiScreen;
    WifiConnectScreen *wifiConnectScreen;
    HistoryScreen *historyScreen;
    bool isAuthenticated;
    QLabel *timeLabel;

    QVector<QWidget *> screens;
    int currentIndex;

    // Navegación entre Widgets
    void moveLeft();
    void moveRight();

    QTimer *refreshTimer;

private slots:
    void showLoginScreen();
    void showHomeScreen();
    void showProductScreen();
    void showRecargaBilleteraScreen();
    void showRecargaMifareScreen();
    void changeToSaleSuccessScreen();
    void changeToMifareSaleSuccessScreen();
    void changeToSaleErrorScreen();
    void changeToMifareSaleErrorScreen();
    void changeBackToRecargaBilletera();
    void changeBackToRecargaMifare();
    void showHistoryScreen();
    void showConfigScreen();
    void setAuthenticated();
    void changeToSaleScreen();
    void changeToMifareSaleScreen();
    void setNotAuthenticated();
    void updateTime();
    void refreshToken();
    void handleTokenReply(QNetworkReply *reply);
    QVariantMap stringToJson(const QString &jsonString);
    void changeToWifiScreen();
    void changeToWifiConnectScreen();
};

#endif // MAINWINDOW_H
