
#ifndef MIFARECLASSIC_H
#define MIFARECLASSIC_H

#include "AcsIncludes.h"

#define MAXIMUM_VALUE 4294967295

enum MIFARE_KEY_TYPE
{
    MIFARE_KEY_TYPE_A = 0x60,
    MIFARE_KEY_TYPE_B = 0x61
};

enum MIFARE_KEY_STORE
{
    MIFARE_KEY_STORE_0 = 0x00,
    MIFARE_KEY_STORE_1 = 0x01
};

enum CARD_TYPE
{
    CARD_TYPE_UNKOWN = 0x00,
    CARD_TYPE_MIFARE_1K = 0x01,
    CARD_TYPE_MIFARE_4K = 0x02,
    CARD_TYPE_MIFARE_PLUS = 0x20
};

class MifareClassic
{
public:
    MifareClassic();

    CARD_TYPE _eCardType;

    void openReader();
    void closeReader();
    void connect();
    void disconnect();
    void loadKey(char *pKey, MIFARE_KEY_STORE eKeyStore);
    void authenticate(MIFARE_KEY_TYPE eKeyType, uint8_t uBlockNumber, MIFARE_KEY_STORE eKeyStore);
    void readBlock(uint8_t uBlockNumber, uint8_t uLength, char *pData);
    void updateBlock(uint8_t uBlockNumber, uint8_t uLength, char *pData);
    void storeValue(uint8_t uBlockNumber, uint64_t uValue);
    void incrementValue(uint8_t uBlockNumber, uint64_t uValue);
    void decrementValue(uint8_t uBlockNumber, uint64_t uValue);
    void readValue(uint8_t uBlockNumber, uint64_t *pValue);
    void restoreValue(uint8_t uSourceBlock, uint8_t uTargetBlock);

private:
};

#endif // MIFARECLASSIC_H
