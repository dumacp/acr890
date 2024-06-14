#ifndef SALESUCCESS_H
#define SALESUCCESS_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QVector>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTimer>

class SaleSuccess : public QWidget
{
    Q_OBJECT

public:
    SaleSuccess(QWidget *parent = 0);
    void startAnimation();

signals:
    void backToBilleteraScreen();

private slots:
    void backToBilleteraScreenSlot();

private:
    QLabel *iconLabel;
    QLabel *textLabel;
    QPushButton *button1;
    QPushButton *button2;
};

#endif // SALESUCCESS_H
