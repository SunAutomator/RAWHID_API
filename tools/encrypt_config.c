#include "../src/config/config.h"
#include "../src/util/crypto.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    BYTE *data;
    DWORD size;
    if (!read_file_into_memory(argv[1], &data, &size)) {
        fprintf(stderr, "Error reading file into memory.\n");
        return 1;
    }
    
    BYTE *encryptedData;
    DWORD encryptedSize;
    if (!EncryptData(data, size, &encryptedData, &encryptedSize)) {
        fprintf(stderr, "Error encrypting data.\n");
        free(data);  // Don't forget to free allocated memory.
        return 1;
    }

    if (!write_data_to_file(argv[1], encryptedData, encryptedSize)) {
        fprintf(stderr, "Error writing encrypted data to file.\n");
        free(data);
        LocalFree(encryptedData); // Clean up encrypted data
        return 1;
    }

    // Cleanup
    free(data);
    LocalFree(encryptedData);

    printf("File encrypted successfully.\n");
    return 0;
}
