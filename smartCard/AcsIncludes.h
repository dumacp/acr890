//-------------------------------------------------------------------------
//
//  Created on:		October 9, 2014
//  Created by:		Rhalf Wendel Caacbay (Lucky)
//
//  Modified on:
//  Modified by:
//
//-------------------------------------------------------------------------
#ifndef ACSINCLUDES_H
#define ACSINCLUDES_H

#endif // ACSINCLUDES_H

// qt
#include <QWidget>
#include <QKeyEvent>
#include <QString>
#include <QMessageBox>
#include <QWidget>
#include <QIcon>
#include <QDebug>
#include <QThread>
#include <QObject>
#include <QDateTime>
#include <QTimer>
#include <QDialog>
#include <QLocale>
#include <QFile>
#include <QCoreApplication>
#include <QDataStream>
#include <QProcess>
#include <QtCore>
#include <QtGui>
// standard
#include <stdint-gcc.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
// local
#include "AcsHelper.h"
#include "AcsReader.h"
#include "AcsKeypad.h"
#include "AcsException.h"

extern "C"
{
#include <acs_api.h>
#include <acs_errno.h>
#include <acs_ioctl.h>
}
