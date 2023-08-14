#include "crypto.h"

BOOL EncryptData(BYTE* pDataIn, DWORD cbDataIn, BYTE** ppDataOut, DWORD* pcbDataOut) {
    DATA_BLOB DataIn;
    DATA_BLOB DataOut;
    BOOL fResult;

    DataIn.pbData = pDataIn;
    DataIn.cbData = cbDataIn;
    fResult = CryptProtectData(
        &DataIn,           // Data to encrypt
        NULL,          // Description (optional)
        NULL,     // Entropy (optional)
        NULL,           // Reserved
        NULL,        // Prompt options
        0,                 // Flags
        &DataOut);        // Encrypted data

    if (fResult) {
        *ppDataOut = DataOut.pbData;
        *pcbDataOut = DataOut.cbData;
    }

    return fResult;
}

BOOL DecryptData(BYTE* pDataIn, DWORD cbDataIn, BYTE** ppDataOut, DWORD* pcbDataOut) {
    DATA_BLOB DataIn;
    DATA_BLOB DataOut;
    BOOL fResult;

    DataIn.pbData = pDataIn;
    DataIn.cbData = cbDataIn;
    fResult = CryptUnprotectData(
        &DataIn,            // Data to decrypt
        NULL,         // Description (optional)
        NULL,      // Entropy (optional)
        NULL,            // Reserved
        NULL,         // Prompt options
        0,                  // Flags
        &DataOut);         // Decrypted data

    if (fResult) {
        *ppDataOut = DataOut.pbData;
        *pcbDataOut = DataOut.cbData;
    }

    return fResult;
}
