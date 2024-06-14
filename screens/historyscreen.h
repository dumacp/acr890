#ifndef HISTORYSCREEN_H
#define HISTORYSCREEN_H
#include <QWidget>
#include <QList>
#include <QStackedWidget>
#include <QDate>
#include <QTime>
#include <QString>
#include <QVBoxLayout>
#include <QString>

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QTextEdit;
QT_END_NAMESPACE

struct SaleRecord
{
    QString serviceType;
    QDate date;
    QTime time;
    QString user;
    int value;

    SaleRecord(const QString &serviceType, const QDate &date, const QTime &time, const QString &user, int value)
        : serviceType(serviceType), date(date), time(time), user(user), value(value) {}
};

//! [class definition]

class HistoryScreen : public QWidget
{
    Q_OBJECT

public:
    HistoryScreen(QWidget *parent = 0);
    void rotateWindow();
    void displaySalesHistory(const QList<SaleRecord> &salesHistory);
    QString formatNumberWithCommas(int number);
    QString formatNumber(int number);

private:
    QLineEdit *nameLine;
    QLineEdit *addressText;
    QVBoxLayout *mainLayout;
    QLabel *resultLabel;
    QString jwtToken;
    QString modifyingText;
};
//! [class definition]

#endif // HISTORYSCREEN_H
