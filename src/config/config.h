#ifndef _CONFIG_H
#define _CONFIG_H
#pragma once

#include "../util/crypto.h"

#include <assert.h>

char* get_decrypted_config(const char* filename);
BOOL read_file_into_memory(const char *filename, BYTE **data, DWORD *size);
BOOL write_data_to_file(const char *filename, BYTE *data, DWORD size);

#endif // _CONFIG_H