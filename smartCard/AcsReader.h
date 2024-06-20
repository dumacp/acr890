//-------------------------------------------------------------------------
//
//  Created on:		October 9, 2014
//  Created by:		Rhalf Wendel Caacbay (Lucky)
//
//  Modified on:
//  Modified by:
//
//-------------------------------------------------------------------------
#ifndef ACSREADER_H
#define ACSREADER_H

#include "AcsIncludes.h"
#include <vector>
#include <sstream> // Para std::stringstream
#include <iomanip> // Para std::hex y std::setfill
#include <QString>
#include <QDebug>
#include <stdint.h>

enum RETURN_STATUS
{
    STATUS_SUCCESS = 0,
    ERROR_OPEN_PICC = -1,
    ERROR_OPEN_ICC = -2,
    ERROR_OPEN_SAM1 = -3,
    ERROR_OPEN_SAM2 = -4,
    ERROR_POWER_ON_PICC = -5,
    ERROR_POWER_ON_ICC = -6,
    ERROR_POWER_ON_SAM1 = -7,
    ERROR_POWER_ON_SAM2 = -8,
    ERROR_TRANSMIT_PICC = -9,
    ERROR_TRANSMIT_ICC = -10,
    ERROR_TRANSMIT_SAM1 = -11,
    ERROR_TRANSMIT_SAM2 = -12,
    ERROR_POWER_OFF_PICC = -13,
    ERROR_POWER_OFF_ICC = -14,
    ERROR_POWER_OFF_SAM1 = -15,
    ERROR_POWER_OFF_SAM2 = -16,
    ERROR_CLOSE_PICC = -17,
    ERROR_CLOSE_ICC = -18,
    ERROR_CLOSE_SAM1 = -19,
    ERROR_CLOSE_SAM2 = -20,
    ERROR_GENERAL = -21
};

enum POLLING_STATUS
{
    CARD_PRESENT = 0,
    NO_CARD_PICC = -1,
    N0_CARD_ICC = -2,
    NO_CARD_SAM1 = -3,
    NO_CARD_SAM2 = -4,
    UNKNOWN = -5
};

enum CARD_READER
{
    READER_PICC = 0x01,
    READER_ICC = 0x02,
    READER_ICC_SAM1 = 0x04,
    READER_ICC_SAM2 = 0x08
};

struct ApduResponse
{
    std::vector<uint8_t> data;
    uint16_t statusWord;
};

struct ParsedApduResponse
{
    QString requestApdu;
    bool isValid;
    QString responseApdu;
};

class AcsReader
{

public:
    AcsReader();
    ~AcsReader();

    int customTransmit(CARD_READER eCardReader, char *pCmd, uint8_t uCmdLen, char *pResp, uint8_t *uRespLen);
    int transmit(CARD_READER eCardReader, char *pCmd, uint8_t uCmdLen, char *pResp, uint8_t *uRespLen);
    int open(enum CARD_READER eCardReader);
    int close(enum CARD_READER eCardReader);
    int powerOn(enum CARD_READER eCardReader, char *pAtr, uint8_t *pAtrLength);
    int powerOff(enum CARD_READER eCardReader);
    int poll(enum CARD_READER eCardReader, uint8_t uType);
    uint8_t statusIcc();
    uint8_t statusPicc();

    ApduResponse parseResponse(char *response, uint8_t responseLength);
    ParsedApduResponse convertToParsedApduResponse(const ApduResponse &apduResponse, const QString &apdu);

private:
    uint8_t uStatusIcc;
    uint8_t uStatusPicc;

    void printDebug(const QByteArray &data);
    void printDebugLong(const QByteArray &data);
};

#endif // ACSREADER_H
