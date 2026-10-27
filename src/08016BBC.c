#include "ffta.h"

/* 0x08016BBC..0x08016BD8: 28 bytes / 14 instructions. */
struct Window08016BBC {
    u8 unknown_00[4];
    void *secondary_buffer;
    u8 unknown_08[0x0A];
    u8 width;
    u8 height;
};

u16 func_08016BBC(const struct Window08016BBC *window)
{
    u16 size = window->width * window->height * 2;

    if (window->secondary_buffer != 0)
        size *= 2;
    return size;
}
