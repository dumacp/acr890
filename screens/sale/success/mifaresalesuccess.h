#ifndef MIFARESALESUCCESS_H
#define MIFARESALESUCCESS_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QVector>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTimer>

class MifareSaleSuccess : public QWidget
{
    Q_OBJECT

public:
    MifareSaleSuccess(QWidget *parent = 0);
    void startAnimation();

signals:
    void backToMifareScreen();

private slots:
    void backToMifareScreenSlot();
    void runPrinter();
    void PrintPage(const char *companyName, const char *tipoServicio, const char *sampleText, const char *dateTime);

private:
    QLabel *iconLabel;
    QLabel *textLabel;
    QPushButton *button1;
    QPushButton *button2;
};

#endif // MIFARESALESUCCESS_H
