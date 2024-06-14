#ifndef SALEERROR_H
#define SALEERROR_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QVector>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

class SaleError : public QWidget
{
    Q_OBJECT

public:
    SaleError(QWidget *parent = 0);
    void startAnimation();

signals:
    void backToBilleteraScreen();

private slots:
    void backToBilleteraScreenSlot();

private:
    QLabel *iconLabel;
    QLabel *textLabel;
    QPushButton *button2;
};

#endif // SALEERROR_H
