#ifndef RAW_HID_MESSAGE_H
#define RAW_HID_MESSAGE_H
#pragma once

#include <stdint.h>

typedef struct {
    uint8_t message_code;
    uint8_t command_code;
    uint8_t data[62];
} HIDMessage;

enum message_codes {
    PING = 0x01,
    STATUS = 0x02,
    COMMAND = 0x03,
    DATA = 0x04,
    ERR = 0x05,
    LOG = 0x06,
};

enum status_codes {
    PASS = 0x20,
    FAIL = 0x21
};

enum command_codes {
    LAUNCH = 0x01
};

enum app_codes {
    CHROME = 0x01,
    VS_CODE = 0x02,
    TERMINAL = 0x03,
    TASK_MANAGER = 0x04
};

#endif // RAW_HID_MESSAGE_H
