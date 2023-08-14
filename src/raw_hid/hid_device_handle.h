#ifndef HID_DEVICE_HANDLE_H
#define HID_DEVICE_HANDLE_H

#include <stdint.h>

#include "../logger/logger.h"
#include "raw_hid_message.h"

typedef struct {
    uint16_t vendor_id;
    uint16_t product_id;
    uint16_t target_usage_page;
    uint8_t target_usage;
} hid_device_usage_config;

typedef void* HIDDeviceHandle;

typedef struct {
    unsigned char data[64];
    size_t length;
} HIDData;

#endif // HID_DEVICE_HANDLE_H