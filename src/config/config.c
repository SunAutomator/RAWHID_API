// config.c

#include "config.h"

char* get_decrypted_config(const char* filename) {
    BYTE *encryptedData;
    DWORD encryptedSize;
    if (!read_file_into_memory(filename, &encryptedData, &encryptedSize)) {
        return NULL;
    }

    BYTE *decryptedData;
    DWORD decryptedSize;
    if (!DecryptData(encryptedData, encryptedSize, &decryptedData, &decryptedSize)) {
        free(encryptedData);
        return NULL;
    }

    char* result = (char *)malloc(decryptedSize + 1);
    if (!result) {
        LocalFree(decryptedData);
        free(encryptedData);
        return NULL;
    }

    memcpy(result, decryptedData, decryptedSize);
    result[decryptedSize] = '\0';

    free(encryptedData);
    LocalFree(decryptedData);
    return result;
}

BOOL write_encrypted_config(const char* filename, const char* data) {
    BYTE *encryptedData;
    DWORD encryptedSize;
    if (!EncryptData((BYTE *)data, strlen(data), &encryptedData, &encryptedSize)) {
        return FALSE;
    }

    BOOL success = write_data_to_file(filename, encryptedData, encryptedSize);
    LocalFree(encryptedData);
    return success;
}

BOOL read_file_into_memory(const char *filename, BYTE **data, DWORD *size) {
    FILE *file = NULL;
    errno_t err = fopen_s(&file, filename, "rb");
    if (err != 0) {
        return FALSE;
    }

    if (!file) return FALSE;

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    assert(file_size >= 0); // Ensure no error
    *size = (DWORD)file_size;
    fseek(file, 0, SEEK_SET);

    *data = (BYTE *)malloc(*size);
    if (!*data) {
        fclose(file);
        return FALSE;
    }

    size_t bytesRead = fread(*data, 1, *size, file);
    fclose(file);

    if (bytesRead != *size) {
        free(*data);
        return FALSE;
    }

    return TRUE;
}

BOOL write_data_to_file(const char *filename, BYTE *data, DWORD size) {
    FILE *file = NULL;
    errno_t err = fopen_s(&file, filename, "rb");
    if (err != 0) {
        return FALSE;
    }

    if (!file) return FALSE;

    size_t bytesWritten = fwrite(data, 1, size, file);
    fclose(file);
    
    return bytesWritten == size;
}
