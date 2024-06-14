#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QWidget>
#include <QList>
/* #include <QtNetwork/QSslError> // Mover la inclusión aquí */

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QTextEdit;
QT_END_NAMESPACE

//! [class definition]
class HomeScreen : public QWidget
{
    Q_OBJECT

public:
    HomeScreen(QWidget *parent = 0);
    void rotateWindow();

    /* signals:
        void sslErrors(const QList<QSslError> &errors); */

    /* private:
        QLineEdit *nameLine;
        QLineEdit *addressText;
        QLabel *resultLabel;
        QString jwtToken; */
};
//! [class definition]

#endif
