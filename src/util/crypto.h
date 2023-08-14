#ifndef crypto_h
#define crypto_h

#include <stdio.h>
#include <windows.h>
#include <wincrypt.h>
#pragma comment(lib, "crypt32.lib")

BOOL ReadEncryptedFile(const char *filename, BYTE **data, DWORD *size);
BOOL EncryptData(BYTE* pDataIn, DWORD cbDataIn, BYTE** ppDataOut, DWORD* pcbDataOut);
BOOL DecryptData(BYTE* pDataIn, DWORD cbDataIn, BYTE** ppDataOut, DWORD* pcbDataOut);

#endif // crypto_h