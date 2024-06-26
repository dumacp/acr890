#ifndef MIFARESALEERROR_H
#define MIFARESALEERROR_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QVector>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

class MifareSaleError : public QWidget
{
    Q_OBJECT

public:
    MifareSaleError(QWidget *parent = 0);
    void startAnimation();

signals:
    void backToMifareScreen();

private slots:
    void backToMifareScreenSlot();

private:
    QLabel *iconLabel;
    QLabel *textLabel;
    QPushButton *button2;
};

#endif // MIFARESALEERROR_H
