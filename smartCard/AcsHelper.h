//-------------------------------------------------------------------------
//
//  Created on:		October 9, 2014
//  Created by:		Rhalf Wendel Caacbay (Lucky)
//
//  Modified on:
//  Modified by:
//
//-------------------------------------------------------------------------
#ifndef ACSHELPER_H
#define ACSHELPER_H

#include "AcsIncludes.h"

class AcsHelper
{

public:
    AcsHelper();
    static uint8_t showInformationBox(QString message);
    static uint8_t showPlainBox(QString message);
    static uint8_t showPlainBox(char *pData, uint8_t uDataLen);
    static uint8_t printDebug(char *pData, uint8_t uDataLen);
    static uint8_t printDebug(uint8_t *pData, uint8_t uDataLen);
    static uint8_t printDebugLong(char *pData, uint64_t uDataLen);
    static uint8_t printDebug(QString label);
    static uint8_t printDebug(uint8_t uNumber);
    static uint8_t printDebug(uint16_t uNumber);
    static uint8_t printDebug(uint64_t uNumber);
    static uint8_t printDebug(char data);

    static uint8_t convertUint64ToBcdLittleEndian(uint64_t uValue, uint8_t iLength, char *pDataOut);
    static uint8_t convertBcdBigEndianToUint64(char *pDataIn, uint8_t uLength, uint64_t *uValue);

    static uint8_t convertBcdLittleEndianToUint64(char *pDataIn, uint8_t uLength, uint64_t *uValue);
    static uint8_t convertUint64ToBcdBigEndian(uint64_t uValue, uint8_t iLength, char *pDataOut);

    static unsigned char toBCD(unsigned char uDecimal);

    void getBytes(char *pString, char *pByteArray);
    bool checkIfValidHexValue(uint8_t uNumber);
    bool checkIfValidHexCharacter(char uCharacter);
};

#endif // ACSHELPER_H
