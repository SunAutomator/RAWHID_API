#include "../src/config/config.h"
#include "../src/util/crypto.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char* data = get_decrypted_config(argv[1]);
    if (!data) {
        fprintf(stderr, "Error reading file into memory.\n");
        return 1;
    }

    printf("%s\n", data);

    // Cleanup
    free(data);

    return 0;

}