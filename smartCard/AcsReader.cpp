//-------------------------------------------------------------------------
//
//  Created on:		October 9, 2014
//  Created by:		Rhalf Wendel Caacbay (Lucky)
//
//  Modified on:
//  Modified by:
//
//-------------------------------------------------------------------------
#include "AcsReader.h"

AcsHelper _cReaderHelper;

AcsReader::AcsReader()
{
}
AcsReader::~AcsReader()
{
}

int AcsReader::open(enum CARD_READER eCardReader)
{
    int iResponse = 0;

    if ((eCardReader & READER_PICC) == READER_PICC)
    {
        if (uStatusPicc == 0)
        {
            iResponse = picc_open();
            if (iResponse)
                return 1;
            uStatusPicc = 0x01;

            iResponse = picc_field_ctrl(PICC_FIELD_ON);
            if (iResponse)
                return 2;
        }
    }
    if ((eCardReader & READER_ICC) == READER_ICC)
    {
        if (uStatusIcc == 0)
        {
            iResponse = icc_open();
            if (iResponse)
                return 1;
            uStatusIcc = 0x01;
        }
    }
    return 0;
}
int AcsReader::close(enum CARD_READER eCardReader)
{
    int iResponse = 0;
    if (uStatusPicc)
    {
        if ((eCardReader & READER_PICC) == READER_PICC)
        {
            iResponse = picc_field_ctrl(PICC_FIELD_OFF);
            if (iResponse)
                return 1;
            uStatusPicc = 0x00;
            iResponse = picc_close();
            if (iResponse)
                return 2;
        }
    }
    if (uStatusIcc)
    {
        if ((eCardReader & READER_ICC) == READER_ICC)
        {
            uStatusIcc = 0x00;
            iResponse = icc_close();
            if (iResponse)
                return 3;
        }
    }

    return 0;
}

int AcsReader::powerOn(enum CARD_READER eCardReader, char *pAtr, uint8_t *pAtrLength)
{
    int iResponse = 0;
    uint8_t uAtrLen = 32;
    unsigned char aAtr[uAtrLen];

    switch (eCardReader)
    {
    case READER_PICC:
    {
        iResponse = picc_power_on(aAtr, &uAtrLen);
        if (iResponse)
        {
            return 1;
        }

        memcpy(pAtr, aAtr, uAtrLen);
        *pAtrLength = uAtrLen;

        uStatusPicc = 1;
        return 0;
    }
    case READER_ICC:
    {
        iResponse = icc_power_on(ICC_SLOT_ID_0, (unsigned char *)aAtr, (unsigned int *)&uAtrLen);
        if (iResponse)
            return 2;

        memset(aAtr, 0, uAtrLen);
        memcpy(pAtr, aAtr, uAtrLen);
        *pAtrLength = uAtrLen;

        char fidi = 0x95;

        iResponse = icc_pps_set(ICC_SLOT_ID_0, (unsigned char)fidi);
        if (iResponse)
            return 3;

        return 0;
    }
    case READER_ICC_SAM1:
    {
        iResponse = icc_power_on(SAM_SLOT_ID_1, (unsigned char *)aAtr, (unsigned int *)&uAtrLen);
        if (iResponse)
            return 4;

        memset(aAtr, 0, uAtrLen);
        memcpy(pAtr, aAtr, uAtrLen);
        *pAtrLength = uAtrLen;

        char fidi = 0x95;

        iResponse = icc_pps_set(SAM_SLOT_ID_1, (unsigned char)fidi);
        if (iResponse)
            return 5;

        return 0;
    }
    case READER_ICC_SAM2:
    {
        iResponse = icc_power_on(SAM_SLOT_ID_2, (unsigned char *)aAtr, (unsigned int *)&uAtrLen);
        if (iResponse)
            return 6;

        memset(aAtr, 0, uAtrLen);
        memcpy(pAtr, aAtr, uAtrLen);
        *pAtrLength = uAtrLen;

        char fidi = 0x95;

        iResponse = icc_pps_set(SAM_SLOT_ID_2, (unsigned char)fidi);
        if (iResponse)
            return 7;

        return 0;
    }
    default:
        return 255;
    }
}
int AcsReader::powerOff(enum CARD_READER eCardReader)
{
    int iResponse = 0;

    switch (eCardReader)
    {
    case READER_PICC:
    {
        iResponse = picc_power_off();
        if (iResponse)
        {
            return 1;
        }
        return 0;
    }
    case READER_ICC:
    {
        iResponse = icc_power_off(ICC_SLOT_ID_0);
        if (iResponse)
        {
            return 2;
        }
        return 0;
    }
    case READER_ICC_SAM1:
    {
        iResponse = icc_power_off(SAM_SLOT_ID_1);
        if (iResponse)
        {
            return 3;
        }
        return 0;
    }
    case READER_ICC_SAM2:
    {
        iResponse = icc_power_off(SAM_SLOT_ID_2);
        if (iResponse)
        {
            return 4;
        }
        return 0;
    }
    default:
        return 255;
    }
}

int AcsReader::poll(enum CARD_READER eCardReader, uint8_t uPollType)
{
    int iResponse = 0;

    switch (eCardReader)
    {
    case READER_PICC:
    {
        struct picc_card piccCard;

        piccCard.type = PICC_TYPE_A;

        switch (uPollType)
        {

        case 0:
            break;
        case 1:
            iResponse = picc_poll_card(&piccCard);
            if (iResponse)
            {
                qDebug() << "iResponse" << iResponse;
                /* printf("Response: ");
                for (size_t i = 0; i < _uCardResponseLength; i++)
                {
                    printf(" %x ", _aCardResponse[i]); // Get ATR
                }
                printf("\n"); */
            }

            break;
        }

        return 0;
    }
    case READER_ICC:
    {
        iResponse = icc_slot_check(ICC_SLOT_ID_0);
        if (iResponse)
            return 1;
        return 0;
    }
    case READER_ICC_SAM1:
    {
        iResponse = icc_slot_check(SAM_SLOT_ID_1);
        if (iResponse)
            return 1;
        return 0;
    }
    case READER_ICC_SAM2:
    {
        iResponse = icc_slot_check(SAM_SLOT_ID_2);
        if (iResponse)
            return 1;
        return 0;
    }
    default:
        return 255;
    }
}

int AcsReader::transmit(CARD_READER eCardReader, char *pCommand, uint8_t uCommandLength, char *pResponse, uint8_t *uResponseLength)
{
    int iResponse = 0;
    unsigned long uLongResponseLength = 0;
    unsigned int uIntResponseLength = 0;

    _cReaderHelper.printDebug(pCommand, uCommandLength);

    switch (eCardReader)
    {
    case READER_PICC:
        iResponse = picc_transmit((unsigned char *)pCommand, (unsigned long)uCommandLength, (unsigned char *)pResponse, &uLongResponseLength);
        _cReaderHelper.printDebugLong(pResponse, uLongResponseLength);

        if (iResponse)
            return iResponse;

        *uResponseLength = uLongResponseLength;
        return 0;

    case READER_ICC:
        iResponse = icc_apdu_transmit(ICC_SLOT_ID_0, (unsigned char *)pCommand, (unsigned int)uCommandLength, (unsigned char *)pResponse, &uIntResponseLength);
        _cReaderHelper.printDebug(pResponse, uIntResponseLength);

        if (iResponse)
            return iResponse;

        *uResponseLength = uIntResponseLength;
        return 0;

    case READER_ICC_SAM1:
        iResponse = icc_apdu_transmit(SAM_SLOT_ID_1, (unsigned char *)pCommand, (unsigned int)uCommandLength, (unsigned char *)pResponse, &uIntResponseLength);
        _cReaderHelper.printDebug(pResponse, uIntResponseLength);

        if (iResponse)
            return iResponse;

        *uResponseLength = uIntResponseLength;
        return 0;

    case READER_ICC_SAM2:
        iResponse = icc_apdu_transmit(SAM_SLOT_ID_2, (unsigned char *)pCommand, (unsigned int)uCommandLength, (unsigned char *)pResponse, &uIntResponseLength);
        _cReaderHelper.printDebug(pResponse, uIntResponseLength);

        if (iResponse)
            return iResponse;

        *uResponseLength = uIntResponseLength;
        return 0;

    default:
        return 255;
    }
}

uint8_t AcsReader::statusIcc()
{
    return uStatusIcc;
}
uint8_t AcsReader::statusPicc()
{
    return uStatusPicc;
}

/* ApduResponse AcsReader::parseResponse(char *response, ulong responseLength, bool mplus)
{
    ApduResponse apduResponse;
    qDebug() << "responseLength" << responseLength;
    if (mplus && responseLength >= 1)
    {
        apduResponse.statusWord = (response[0] << 8) | 0x00;
        apduResponse.data = QByteArray::fromRawData(response, responseLength);
    }
    else if (responseLength >= 2)
    {
        apduResponse.statusWord = (response[responseLength - 2] << 8) | response[responseLength - 1];

        qDebug() << "apduResponse.statusWord" << apduResponse.statusWord;
        apduResponse.data = QByteArray::fromRawData(response, responseLength - 2);
    }
    else
    {
        apduResponse.statusWord = 0;
        apduResponse.data.clear();
    }
    return apduResponse;
} */

ApduResponse AcsReader::parseResponse(char *response, ulong responseLength, bool mplus)
{
    ApduResponse apduResponse;

    qDebug() << "responseLength:" << responseLength;
    qDebug() << "response data:" << QByteArray::fromRawData(response, responseLength).toHex();

    if (responseLength >= 2)
    {
        uint8_t highByte = static_cast<uint8_t>(response[responseLength - 2]);
        uint8_t lowByte = static_cast<uint8_t>(response[responseLength - 1]);
        apduResponse.statusWord = (highByte << 8) | lowByte;

        qDebug() << "Extracted statusWord (hex):" << QString::number(apduResponse.statusWord, 16).toUpper();

        /*  if (apduResponse.statusWord == 0x9000)
         {
             apduResponse.isValid = true;
         }
         else
         {
             apduResponse.isValid = false;
         } */
    }

    qDebug() << "Final apduResponse.statusWord:" << QString::number(apduResponse.statusWord, 16).toUpper();

    // Aquí puedes extraer los datos restantes según sea necesario
    apduResponse.data = QByteArray(response, responseLength);

    qDebug() << "Final apduResponse.data:" << apduResponse.data.toHex();

    return apduResponse;
}

void AcsReader::printDebug(const QByteArray &data)
{
    qDebug() << "Debug:" << data.toHex();
}

void AcsReader::printDebugLong(const QByteArray &data)
{
    qDebug() << "Debug Long:" << data.toHex();
}

int AcsReader::customTransmit(CARD_READER eCardReader, char *pCommand, uint8_t commandLength, char *pResponse, ulong *responseLength)
{
    int iResponse = 0;
    unsigned long uLongResponseLength = 0;
    unsigned int uIntResponseLength = 0;

    QByteArray commandArray = QByteArray::fromHex(pCommand);

    // qDebug() << "commandArray: " << QString::fromLatin1(commandArray);
    // printDebug(commandArray);

    switch (eCardReader)
    {
    case READER_PICC:
        iResponse = picc_transmit(reinterpret_cast<unsigned char *>(const_cast<char *>(commandArray.data())), commandArray.size(), reinterpret_cast<unsigned char *>(pResponse), &uLongResponseLength);
        printDebugLong(QByteArray(pResponse, uLongResponseLength));

        if (iResponse)
            return iResponse;

        *responseLength = static_cast<ulong>(uLongResponseLength);
        return 0;

    case READER_ICC:
        iResponse = icc_apdu_transmit(ICC_SLOT_ID_0, reinterpret_cast<unsigned char *>(const_cast<char *>(commandArray.data())), commandArray.size(), reinterpret_cast<unsigned char *>(pResponse), &uIntResponseLength);
        printDebug(QByteArray(pResponse, uIntResponseLength));

        if (iResponse)
            return iResponse;

        /* *responseLength = static_cast<uint8_t>(uIntResponseLength); */
        *responseLength = static_cast<ulong>(uIntResponseLength);
        return 0;

    case READER_ICC_SAM1:
        iResponse = icc_apdu_transmit(SAM_SLOT_ID_1, reinterpret_cast<unsigned char *>(const_cast<char *>(commandArray.data())), commandArray.size(), reinterpret_cast<unsigned char *>(pResponse), &uIntResponseLength);
        printDebug(QByteArray(pResponse, uIntResponseLength));

        if (iResponse)
            return iResponse;

        *responseLength = static_cast<uint8_t>(uIntResponseLength);
        return 0;

    case READER_ICC_SAM2:
        iResponse = icc_apdu_transmit(SAM_SLOT_ID_2, reinterpret_cast<unsigned char *>(const_cast<char *>(commandArray.data())), commandArray.size(), reinterpret_cast<unsigned char *>(pResponse), &uIntResponseLength);
        printDebug(QByteArray(pResponse, uIntResponseLength));

        if (iResponse)
            return iResponse;

        *responseLength = static_cast<uint8_t>(uIntResponseLength);
        return 0;

    default:
        return 255;
    }
}

/* ParsedApduResponse AcsReader::convertToParsedApduResponse(const ApduResponse &apduResponse, const QString &apdu)
{
    ParsedApduResponse parsedResponse;
    qDebug() << "statusWord convertToParsedApduResponse:" << QString::number(apduResponse.statusWord, 16).toUpper();
    parsedResponse.requestApdu = apdu;
    qDebug() << "Comparando statusWord:" << QString::number(apduResponse.statusWord, 16).toUpper() << "con 0x9000";
    parsedResponse.isValid = (apduResponse.statusWord == 0x9000);
    parsedResponse.responseApdu = apduResponse.data.toHex();
    qDebug() << "isValid:" << parsedResponse.isValid;
    return parsedResponse;
} */

ParsedApduResponse AcsReader::convertToParsedApduResponse(const ApduResponse &apduResponse, const QString &apdu)
{
    ParsedApduResponse parsedResponse;
    parsedResponse.requestApdu = apdu;

    qDebug() << "statusWord (hex):" << QString::number(apduResponse.statusWord, 16).toUpper();
    qDebug() << "statusWord (dec):" << apduResponse.statusWord;
    qDebug() << "Comparando statusWord con 0x9000";
    qDebug() << "0x9000 (dec):" << 0x9000;

    uint16_t expectedStatusWord = 0x9000;
    qDebug() << "expectedStatusWord (hex):" << QString::number(expectedStatusWord, 16).toUpper();
    qDebug() << "expectedStatusWord (dec):" << expectedStatusWord;

    parsedResponse.isValid = (apduResponse.statusWord == expectedStatusWord);

    qDebug() << "isValid:" << parsedResponse.isValid;

    parsedResponse.responseApdu = apduResponse.data.toHex();
    return parsedResponse;
}