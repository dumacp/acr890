//-------------------------------------------------------------------------
//
//  Created on:		October 9, 2014
//  Created by:		Rhalf Wendel Caacbay (Lucky)
//
//  Modified on:
//  Modified by:
//
//-------------------------------------------------------------------------
#include "AcsHelper.h"

AcsHelper::AcsHelper()
{
}

uint8_t AcsHelper::showInformationBox(QString message)
{
    QIcon icon("/");
    QMessageBox *msgBox = new QMessageBox(QMessageBox::Information,
                                          "ACS",
                                          message,
                                          QMessageBox::Ok, 0);
    msgBox->setWindowIcon(icon);
    msgBox->setStyleSheet("QMessageBox { background-color: #FF2222; border: 2px solid black; padding: 5px;} QPushButton {background-color: #FFFFFF;} QLabel {color:#FFFFFF;font-size:12px; font-weight:bold;}");
    msgBox->exec();

    return 0;
}

uint8_t AcsHelper::showPlainBox(QString message)
{
    QIcon icon("/");
    QMessageBox *msgBox = new QMessageBox(QMessageBox::NoIcon,
                                          "ACS",
                                          message,
                                          QMessageBox::Ok, 0);
    msgBox->setWindowIcon(icon);
    msgBox->setStyleSheet("QMessageBox { background-color: #FF2222; border: 2px solid black; padding: 5px;} QPushButton {background-color: #FFFFFF;} QLabel {color:#FFFFFF;font-size:12px; font-weight:bold;}");
    msgBox->exec();

    return 0;
}

uint8_t AcsHelper::showPlainBox(char *pData, uint8_t uDataLen)
{
    QByteArray aRespBytes = QByteArray((const char *)pData, uDataLen);
    QIcon icon("/");
    QMessageBox *msgBox = new QMessageBox(QMessageBox::NoIcon,
                                          "ACS",
                                          QString(aRespBytes.toHex()).toUtf8().constData(),
                                          QMessageBox::Ok, 0);
    msgBox->setWindowIcon(icon);
    msgBox->setStyleSheet("QMessageBox { background-color: #FF2222; border: 2px solid black; padding: 5px;} QPushButton {background-color: #FFFFFF;} QLabel {color:#FFFFFF;font-size:12px; font-weight:bold;}");
    msgBox->setFixedWidth(240);
    msgBox->setTextFormat(Qt::RichText);
    msgBox->exec();

    return 0;
}

uint8_t AcsHelper::printDebug(char *pData, uint8_t uDataLen)
{
    QByteArray aRespBytes = QByteArray(pData, uDataLen);
    qDebug() << QString(aRespBytes.toHex()).toUtf8().constData();
    return 0;
}
uint8_t AcsHelper::printDebug(uint8_t *pData, uint8_t uDataLen)
{
    QByteArray aRespBytes = QByteArray((const char *)pData, uDataLen);
    qDebug() << QString(aRespBytes.toHex()).toUtf8().constData();
    return 0;
}
uint8_t AcsHelper::printDebugLong(char *pData, uint64_t uDataLen)
{
    QByteArray aRespBytes = QByteArray((const char *)pData, uDataLen);
    qDebug() << QString(aRespBytes.toHex()).toUtf8().constData();
    return 0;
}
uint8_t AcsHelper::printDebug(QString label)
{
    qDebug() << label;
    return 0;
}

uint8_t AcsHelper::printDebug(uint8_t uNumber)
{
    qDebug() << QString::number(uNumber);
    return 0;
}
uint8_t AcsHelper::printDebug(uint16_t uNumber)
{
    qDebug() << QString::number(uNumber);
    return 0;
}
uint8_t AcsHelper::printDebug(uint64_t uNumber)
{
    qDebug() << QString::number(uNumber);
    return 0;
}
uint8_t AcsHelper::printDebug(char data)
{
    qDebug() << QString::number(data, 16);
    return 0;
}

//++++++++++++++++++++++++++++++++++++++++++++
uint8_t AcsHelper::convertBcdBigEndianToUint64(char *pDataIn, uint8_t uLength, uint64_t *uValue)
{
    if (uLength > 4)
        return 1;

    if (uLength == 4)
        *uValue = ((uint64_t)pDataIn[0] << 24) + ((uint64_t)pDataIn[1] << 16) + ((uint64_t)pDataIn[2] << 8) + (uint64_t)pDataIn[3];

    if (uLength == 3)
        *uValue = ((uint64_t)pDataIn[0] << 16) + ((uint64_t)pDataIn[1] << 8) + (uint64_t)pDataIn[2];

    if (uLength == 2)
        *uValue = ((uint64_t)pDataIn[0] << 8) + (uint64_t)pDataIn[1];

    return 0;
}
uint8_t AcsHelper::convertBcdLittleEndianToUint64(char *pDataIn, uint8_t uLength, uint64_t *uValue)
{
    if (uLength > 4)
        return 1;

    if (uLength == 4)
        *uValue = ((uint64_t)pDataIn[3] << 24) + ((uint64_t)pDataIn[2] << 16) + ((uint64_t)pDataIn[1] << 8) + (uint64_t)pDataIn[0];

    if (uLength == 3)
        *uValue = ((uint64_t)pDataIn[2] << 16) + ((uint64_t)pDataIn[1] << 8) + (uint64_t)pDataIn[0];

    if (uLength == 2)
        *uValue = ((uint64_t)pDataIn[1] << 8) + (uint64_t)pDataIn[0];

    return 0;
}
uint8_t AcsHelper::convertUint64ToBcdLittleEndian(uint64_t uValue, uint8_t iLength, char *pDataOut)
{

    if (iLength == 4)
    {
        pDataOut[0] = uValue & 0xFF;
        pDataOut[1] = (uValue >> 8) & 0xFF;
        pDataOut[2] = (uValue >> 16) & 0xFF;
        pDataOut[3] = (uValue >> 24) & 0xFF;
    }
    if (iLength == 3)
    {
        pDataOut[0] = uValue & 0xFF;
        pDataOut[1] = (uValue >> 8) & 0xFF;
        pDataOut[2] = (uValue >> 16) & 0xFF;
    }
    if (iLength == 2)
    {
        pDataOut[0] = uValue & 0xFF;
        pDataOut[1] = (uValue >> 8) & 0xFF;
    }
    return 0;
}
uint8_t AcsHelper::convertUint64ToBcdBigEndian(uint64_t uValue, uint8_t iLength, char *pDataOut)
{

    if (iLength == 4)
    {
        pDataOut[3] = uValue & 0xFF;
        pDataOut[2] = (uValue >> 8) & 0xFF;
        pDataOut[1] = (uValue >> 16) & 0xFF;
        pDataOut[0] = (uValue >> 24) & 0xFF;
    }
    if (iLength == 3)
    {
        pDataOut[2] = uValue & 0xFF;
        pDataOut[1] = (uValue >> 8) & 0xFF;
        pDataOut[0] = (uValue >> 16) & 0xFF;
    }
    if (iLength == 2)
    {
        pDataOut[1] = uValue & 0xFF;
        pDataOut[0] = (uValue >> 8) & 0xFF;
    }
    return 0;
}

unsigned char AcsHelper::toBCD(unsigned char uDecimal)
{
    if (uDecimal > 99)
    {
        // this must not occur throw an exception here
        return -1;
    }

    unsigned char uResult = 0;
    unsigned char uMSN;
    unsigned char uLSN;

    uMSN = (uDecimal / 10);
    uLSN = (uDecimal % 10);

    uResult = (uint8_t)(uMSN << 4 | uLSN);

    return uResult;
}

void AcsHelper::getBytes(char *pString, char *pByteArray)
{
    char aBuffer[10];
    int iResult = 0;
    int iLength = strlen(pString);

    if (iLength == 0 || iLength % 2 != 0)
        return;

    for (int iCounter1 = 0, iCounter2 = 0; iCounter1 < iLength; iCounter1 += 2, iCounter2++)
    {
        memcpy(aBuffer, pString + iCounter1, 2);
        sscanf(aBuffer, "%02X", &iResult);
        pByteArray[iCounter2] = (char)iResult;
    }
}

bool AcsHelper::checkIfValidHexValue(uint8_t uNumber)
{
    uint8_t aNumber[2];
    uint8_t uCounter = 0;

    aNumber[0] = (uNumber & 0xF0) >> 4;
    aNumber[1] = uNumber & 0x0F;

    for (uCounter = 0; uCounter < 2; uCounter++)
    {
        switch (aNumber[uCounter])
        {
        case 0x00:
        case 0x01:
        case 0x02:
        case 0x03:
        case 0x04:
        case 0x05:
        case 0x06:
        case 0x07:
        case 0x08:
        case 0x09:
        case 0x0A:
        case 0x0B:
        case 0x0C:
        case 0x0D:
        case 0x0E:
        case 0x0F:
            break;
        default:
            return false;
        }
    }

    return true;
}

bool AcsHelper::checkIfValidHexCharacter(char uCharacter)
{
    switch (uCharacter)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
        break;
    default:
        return false;
    }

    return true;
}
