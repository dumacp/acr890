#ifndef WIFISETUPSCREEN_H
#define WIFISETUPSCREEN_H
#include <QWidget>
#include <QList>
#include <QStackedWidget>
#include <QDate>
#include <QTime>
#include <QString>
#include <QVBoxLayout>
#include <QString>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QTextEdit;
QT_END_NAMESPACE

//! [class definition]

class WifiScreen : public QWidget
{
    Q_OBJECT

public:
    WifiScreen(QWidget *parent = 0);
    void rotateWindow();
    void displaySalesHistory(const QList<QString> &salesHistory);
    ~WifiScreen();

protected:
    void showEvent(QShowEvent *event);

signals:
    void changeToWifiConnect();

private slots:
    void handleCellDoubleClicked(int row, int column);
    void scanResults();

private:
    QLineEdit *nameLine;
    QLineEdit *addressText;
    QVBoxLayout *mainLayout;
    QLabel *resultLabel;
    QString jwtToken;
    QString modifyingText;
    QTableWidget *salesTable;
    QStringList scanResultsList;
};
//! [class definition]

#endif // WIFISETUPSCREEN_H
