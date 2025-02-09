#ifndef CONFIGSCREEN_H
#define CONFIGSCREEN_H

#include <QWidget>
#include <QList>
#include <QStackedWidget>

// Led test
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

// standard
#include <stdint-gcc.h>
#include <stdint.h>
#include <vector>

// Net
#include <QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include "../smartCard/MifareClassic.h"
#include "../smartCard/AcsHelper.h"
#include "../smartCard/AcsReader.h"
#include "../smartCard/AcsException.h"

//! [class definition]
class ConfigScreen : public QWidget
{
    Q_OBJECT

public:
    ConfigScreen(QWidget *parent = 0);
    void rotateWindow();

signals:
    void changeToWifiSetup();

public slots:
    void runLed();
    void turnOffLed(); // Nuevo slot para apagar el LED
    void goToWifiSettings();
};
//! [class definition]

#endif // CONFIGSCREEN_H
