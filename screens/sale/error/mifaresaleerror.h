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
    void handleChangeText(const QString &text);

signals:
    void backToMifareScreen();
    void backToMifareSaleProgressScreen();

private slots:
    void backToMifareScreenSlot();
    void backToMifareSaleProgressSlot();

private:
    QLabel *iconLabel;
    QLabel *textLabel;
    QLabel *additionalTextLabel;
};

#endif // MIFARESALEERROR_H
