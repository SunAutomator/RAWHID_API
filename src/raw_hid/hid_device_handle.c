#include "hid_device_handle.h"

#include <stdio.h>
#include <hidapi.h>
#include <synchapi.h>
#include <time.h>
#include <windows.h>

#define RESPONSE_INDICATOR_BYTE 0x01
#define SUCCESS_CODE_BYTE 0x20

// Represents the HID device handle.
typedef hid_device* HIDDeviceHandle;

HIDDeviceHandle hid_open_device(hid_device_usage_config usage_config) {
    HIDDeviceHandle handle = hid_open(hid_device_usage_config.vendor_id, hid_device_usage_config.usage_page, NULL);
    if (handle) {
        struct hid_device_info *info = hid_enumerate(hid_device_usage_config.vendor_id, hid_device_usage_config.product_id);
        while (info) {
            if (info->usage_page == hid_device_usage_config.target_usage_page && info->usage == hid_device_usage_config.target_usage) {
                handle = hid_open_path(info->path);
                if (handle) {
                    break;
                }
            }
            info = info->next;
        }
        hid_free_enumeration(info);
    }

    return handle;
}

// Function to close the HID device handle.
void hid_close_device(HIDDeviceHandle handle) {
    hid_close(handle);
}

// Function to read data from the HID device handle.
HIDData* hid_read_data(HIDDeviceHandle handle) {
    static HIDData data;
    int res = hid_read(handle, data.data, sizeof(data.data));
    if (res > 0) {
        data.length = res;
        return &data;
    }
    return NULL;
}

int write_to_handle(HIDDeviceHandle handle, unsigned char* message, size_t size) {
    return hid_write(handle, message, size);
}

void print_message(unsigned char* message, size_t size) {
    for (size_t i = 0; i < size; i++) {
        fprintf(stderr, "%02X ", message[i]);
    }
    fprintf(stderr, "\n");
}

void send_ping(HIDDeviceHandle handle) {
    unsigned char ping[64] = {0x01, 0x01, 0x02};
    if (write_to_handle(handle, ping, sizeof(ping)) < 0) {
        fprintf(stderr, "Failed to send ping: %s\n", hid_error(handle));
    } else {
        fprintf(stderr, "Sent ping: ");
        print_message(ping, sizeof(ping));
    }
}
