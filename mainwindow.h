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
#include "screens/sale/animation/saleprogress.h"
#include "screens/sale/success/salesuccess.h"
#include "screens/sale/error/saleerror.h"
#include "screens/historyscreen.h"
#include "screens/configscreen.h"

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
    SaleProgress *saleProgress;
    SaleSuccess *saleSuccess;
    SaleError *saleError;
    ConfigScreen *configScreen;
    HistoryScreen *historyScreen;
    bool isAuthenticated;
    QLabel *timeLabel;

    QVector<QWidget *> screens;
    int currentIndex;

    // Navegación entre Widgets
    void moveLeft();
    void moveRight();

private slots:
    void showLoginScreen();
    void showHomeScreen();
    void showProductScreen();
    void showRecargaBilleteraScreen();
    void changeToSaleSuccessScreen();
    void changeToSaleErrorScreen();
    void changeBackToRecargaBilletera();
    void showHistoryScreen();
    void showConfigScreen();
    void setAuthenticated();
    void changeToSaleScreen();
    void setNotAuthenticated();
    void updateTime();
};

#endif // MAINWINDOW_H
