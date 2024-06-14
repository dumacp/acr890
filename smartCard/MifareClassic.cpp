#include "MifareClassic.h"

int8_t _iReaderResponse;

char _aCardCommand[256];
uint8_t _uCardCommandLength;
char _aCardResponse[256];
uint8_t _uCardResponseLength;

AcsReader _cReader;
AcsHelper _cHelper;
AcsException _cExpection;

MifareClassic::MifareClassic()
{
}

void MifareClassic::openReader()
{
    _iReaderResponse = _cReader.open(READER_PICC);
    if (_iReaderResponse != STATUS_SUCCESS)
    {
        _cExpection.sMessage = "Open PICC failed";
        _cExpection.iNumber = _iReaderResponse;
        throw _cExpection;
    }
}

void MifareClassic::closeReader()
{
    _cReader.close(READER_PICC);
}

void MifareClassic::connect()
{
    _iReaderResponse = _cReader.powerOn(READER_PICC, _aCardResponse, &_uCardResponseLength);
    printf("Response: ");
    for (size_t i = 0; i < _uCardResponseLength; i++)
    {
        printf(" %x ", _aCardResponse[i]);
    }
    printf("\n");

    // qDebug() << "_aCardResponse =" << _aCardResponse;
    if (_iReaderResponse != STATUS_SUCCESS)
    {
        _cExpection.sMessage = "Power On PICC failed";
        _cExpection.iNumber = _iReaderResponse;
        throw _cExpection;
    }

    if (_uCardResponseLength < 15)
    {
        _cExpection.sMessage = "Invalid Mifare Card";
        _cExpection.iNumber = _iReaderResponse;
        throw _cExpection;
    }

    if (_aCardResponse[13] != 0x00)
    {
        _cExpection.sMessage = "Invalid Mifare Card";
        _cExpection.iNumber = _iReaderResponse;
        throw _cExpection;
    }

    if (_aCardResponse[14] != 0x01 && _aCardResponse[14] != 0x02)
    {
        _cExpection.sMessage = "Invalid Mifare Card";
        _cExpection.iNumber = _iReaderResponse;
        throw _cExpection;
    }

    if (_aCardResponse[14] == 0x01)
        _eCardType = CARD_TYPE_MIFARE_1K;
    else if (_aCardResponse[14] == 0x02)
        _eCardType = CARD_TYPE_MIFARE_4K;
    else
        _eCardType = CARD_TYPE_UNKOWN;
}

void MifareClassic::disconnect()
{
    _cReader.powerOff(READER_PICC);
}

void MifareClassic::loadKey(char *pKey, MIFARE_KEY_STORE eKeyStore)
{
    memcpy(_aCardCommand, "\xFF\x82\x00\x00\x06\x00\x00\x00\x00\x00\x00", 11);
    _aCardCommand[3] = eKeyStore;
    memcpy(_aCardCommand + 5, pKey, 6);

    _iReaderResponse = _cReader.transmit(READER_PICC, _aCardCommand, 11, _aCardResponse, &_uCardResponseLength);
    if (_iReaderResponse != STATUS_SUCCESS)
    {
        _cExpection.sMessage = "Load key failed";
        _cExpection.iNumber = _iReaderResponse;
        throw _cExpection;
    }

    if (_uCardResponseLength != 2)
    {
        _cExpection.sMessage = "Load key failed";
        _cExpection.iNumber = _iReaderResponse;
        throw _cExpection;
    }

    if (_aCardResponse[0] != 0x90 || _aCardResponse[1] != 0x00)
    {
        _cExpection.sMessage = "Load key failed";
        _cExpection.iNumber = _iReaderResponse;
        memcpy(_cExpection.aStatusWord, _aCardResponse, 2);
        throw _cExpection;
    }
}

void MifareClassic::authenticate(MIFARE_KEY_TYPE eKeyType, uint8_t uBlockNumber, MIFARE_KEY_STORE eKeyStore)
{
    memcpy(_aCardCommand, "\xFF\x86\x00\x00\x05\x01\x00\x00\x00\x00", 10);
    _aCardCommand[7] = uBlockNumber;
    _aCardCommand[8] = eKeyType;
    _aCardCommand[9] = eKeyStore;

    _iReaderResponse = _cReader.transmit(READER_PICC, _aCardCommand, 10, _aCardResponse, &_uCardResponseLength);
    if (_iReaderResponse != STATUS_SUCCESS)
    {
        _cExpection.sMessage = "Authentication failed";
        _cExpection.iNumber = _iReaderResponse;
        throw _cExpection;
    }

    if (_uCardResponseLength != 2)
    {
        _cExpection.sMessage = "Authentication failed";
        _cExpection.iNumber = _iReaderResponse;
        throw _cExpection;
    }

    if (_aCardResponse[0] != 0x90 || _aCardResponse[1] != 0x00)
    {
        _cExpection.sMessage = "Authentication failed";
        _cExpection.iNumber = _iReaderResponse;
        memcpy(_cExpection.aStatusWord, _aCardResponse, 2);
        throw _cExpection;
    }
}

void MifareClassic::readBlock(uint8_t uBlockNumber, uint8_t uLength, char *pData)
{
    memcpy(_aCardCommand, "\xFF\xB0\x00\x00\x00", 5);
    _aCardCommand[3] = uBlockNumber;
    _aCardCommand[4] = uLength;

    _iReaderResponse = _cReader.transmit(READER_PICC, _aCardCommand, 5, _aCardResponse, &_uCardResponseLength);
    if (_iReaderResponse != STATUS_SUCCESS)
    {
        _cExpection.sMessage = "Read block failed";
        _cExpection.iNumber = _iReaderResponse;
        throw _cExpection;
    }

    if (_aCardResponse[_uCardResponseLength - 2] != 0x90 || _aCardResponse[_uCardResponseLength - 1] != 0x00)
    {
        _cExpection.sMessage = "Read block failed";
        _cExpection.iNumber = _iReaderResponse;
        memcpy(_cExpection.aStatusWord, _aCardResponse + _uCardResponseLength - 2, 2);
        throw _cExpection;
    }

    memcpy(pData, _aCardResponse, _uCardResponseLength - 2);
}

void MifareClassic::updateBlock(uint8_t uBlockNumber, uint8_t uLength, char *pData)
{
    memcpy(_aCardCommand, "\xFF\xD6\x00\x00\x00", 5);
    _aCardCommand[3] = uBlockNumber;
    _aCardCommand[4] = uLength;
    memcpy(_aCardCommand + 5, pData, uLength);

    _iReaderResponse = _cReader.transmit(READER_PICC, _aCardCommand, uLength + 5, _aCardResponse, &_uCardResponseLength);
    if (_iReaderResponse != STATUS_SUCCESS)
    {
        _cExpection.sMessage = "Update block failed";
        _cExpection.iNumber = _iReaderResponse;
        throw _cExpection;
    }

    if (_aCardResponse[0] != 0x90 || _aCardResponse[1] != 0x00)
    {
        _cExpection.sMessage = "Update block failed";
        _cExpection.iNumber = _iReaderResponse;
        memcpy(_cExpection.aStatusWord, _aCardResponse, 2);
        throw _cExpection;
    }
}

void MifareClassic::storeValue(uint8_t uBlockNumber, uint64_t uValue)
{
    memcpy(_aCardCommand, "\xFF\xD7\x00\x00\x05\x00", 6);
    _aCardCommand[3] = uBlockNumber;
    _cHelper.convertUint64ToBcdBigEndian(uValue, 4, _aCardCommand + 6);

    _iReaderResponse = _cReader.transmit(READER_PICC, _aCardCommand, 10, _aCardResponse, &_uCardResponseLength);
    if (_iReaderResponse != STATUS_SUCCESS)
    {
        _cExpection.sMessage = "Store value failed";
        _cExpection.iNumber = _iReaderResponse;
        throw _cExpection;
    }

    if (_aCardResponse[0] != 0x90 || _aCardResponse[1] != 0x00)
    {
        _cExpection.sMessage = "Store value failed";
        _cExpection.iNumber = _iReaderResponse;
        memcpy(_cExpection.aStatusWord, _aCardResponse, 2);
        throw _cExpection;
    }
}

void MifareClassic::incrementValue(uint8_t uBlockNumber, uint64_t uValue)
{
    memcpy(_aCardCommand, "\xFF\xD7\x00\x00\x05\x01", 6);
    _aCardCommand[3] = uBlockNumber;
    _cHelper.convertUint64ToBcdBigEndian(uValue, 4, _aCardCommand + 6);

    _iReaderResponse = _cReader.transmit(READER_PICC, _aCardCommand, 10, _aCardResponse, &_uCardResponseLength);
    if (_iReaderResponse != STATUS_SUCCESS)
    {
        _cExpection.sMessage = "Increment value failed";
        _cExpection.iNumber = _iReaderResponse;
        throw _cExpection;
    }

    if (_aCardResponse[0] != 0x90 || _aCardResponse[1] != 0x00)
    {
        _cExpection.sMessage = "Increment value failed";
        _cExpection.iNumber = _iReaderResponse;
        memcpy(_cExpection.aStatusWord, _aCardResponse, 2);
        throw _cExpection;
    }
}

void MifareClassic::decrementValue(uint8_t uBlockNumber, uint64_t uValue)
{
    memcpy(_aCardCommand, "\xFF\xD7\x00\x00\x05\x02", 6);
    _aCardCommand[3] = uBlockNumber;
    _cHelper.convertUint64ToBcdBigEndian(uValue, 4, _aCardCommand + 6);

    _iReaderResponse = _cReader.transmit(READER_PICC, _aCardCommand, 10, _aCardResponse, &_uCardResponseLength);
    if (_iReaderResponse != STATUS_SUCCESS)
    {
        _cExpection.sMessage = "Decrement value failed";
        _cExpection.iNumber = _iReaderResponse;
        throw _cExpection;
    }

    if (_aCardResponse[0] != 0x90 || _aCardResponse[1] != 0x00)
    {
        _cExpection.sMessage = "Decrement value failed";
        _cExpection.iNumber = _iReaderResponse;
        memcpy(_cExpection.aStatusWord, _aCardResponse, 2);
        throw _cExpection;
    }
}

void MifareClassic::readValue(uint8_t uBlockNumber, uint64_t *pValue)
{
    memcpy(_aCardCommand, "\xFF\xB1\x00\x00\x04", 5);
    _aCardCommand[3] = uBlockNumber;

    _iReaderResponse = _cReader.transmit(READER_PICC, _aCardCommand, 5, _aCardResponse, &_uCardResponseLength);
    if (_iReaderResponse != STATUS_SUCCESS)
    {
        _cExpection.sMessage = "Read value failed";
        _cExpection.iNumber = _iReaderResponse;
        throw _cExpection;
    }

    if (_aCardResponse[_uCardResponseLength - 2] != 0x90 || _aCardResponse[_uCardResponseLength - 1] != 0x00)
    {
        _cExpection.sMessage = "Read value failed";
        _cExpection.iNumber = _iReaderResponse;
        memcpy(_cExpection.aStatusWord, _aCardResponse + _uCardResponseLength - 2, 2);
        throw _cExpection;
    }

    _cHelper.convertBcdBigEndianToUint64(_aCardResponse, 4, pValue);
}

void MifareClassic::restoreValue(uint8_t uSourceBlock, uint8_t uTargetBlock)
{
    memcpy(_aCardCommand, "\xFF\xD7\x00\x00\x02\x03\x00", 7);
    _aCardCommand[3] = uSourceBlock;
    _aCardCommand[6] = uTargetBlock;

    _iReaderResponse = _cReader.transmit(READER_PICC, _aCardCommand, 7, _aCardResponse, &_uCardResponseLength);
    if (_iReaderResponse != STATUS_SUCCESS)
    {
        _cExpection.sMessage = "Restore value failed";
        _cExpection.iNumber = _iReaderResponse;
        throw _cExpection;
    }

    if (_aCardResponse[0] != 0x90 || _aCardResponse[1] != 0x00)
    {
        _cExpection.sMessage = "Restore value failed";
        _cExpection.iNumber = _iReaderResponse;
        memcpy(_cExpection.aStatusWord, _aCardResponse, 2);
        throw _cExpection;
    }
}
