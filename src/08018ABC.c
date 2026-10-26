#include "ffta.h"

/* Complete target: [0x08018ABC, 0x08018C24), 360 bytes. */
u16 func_08018ABC(u8 *buffer, u32 value)
{
    u16 digit_base = 0x8118;
    u8 *output = buffer;
    u8 started = 0;
    u16 digit = 0;

    while (value >= 1000000) {
        value -= 1000000;
        digit++;
        started = 1;
    }
    if (digit != 0) {
        digit += digit_base;
        *output++ = digit >> 8;
        *output++ = digit;
    }

    digit = 0;
    while (value >= 100000) {
        value -= 100000;
        digit++;
        started = 1;
    }
    if (digit != 0 || started) {
        digit += digit_base;
        *output++ = digit >> 8;
        *output++ = digit;
    }

    digit = 0;
    while (value >= 10000) {
        value -= 10000;
        digit++;
        started = 1;
    }
    if (digit != 0 || started) {
        digit += digit_base;
        *output++ = digit >> 8;
        *output++ = digit;
    }

    digit = 0;
    while (value >= 1000) {
        value -= 1000;
        digit++;
        started = 1;
    }
    if (digit != 0 || started) {
        digit += digit_base;
        *output++ = digit >> 8;
        *output++ = digit;
    }

    digit = 0;
    while (value >= 100) {
        value -= 100;
        digit++;
        started = 1;
    }
    if (digit != 0 || started) {
        digit += digit_base;
        *output++ = digit >> 8;
        *output++ = digit;
    }

    digit = 0;
    while (value >= 10) {
        value -= 10;
        digit++;
        started = 1;
    }
    if (digit != 0 || started) {
        digit += digit_base;
        *output++ = digit >> 8;
        *output++ = digit;
    }

    digit = value;
    digit += digit_base;
    *output++ = digit >> 8;
    *output++ = digit;
    *output = 0;
    return output - buffer;
}
