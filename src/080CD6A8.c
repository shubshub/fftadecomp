#include "ffta.h"

extern u8 func_080C8280(const void *object);

static inline u8 flag_e8_40(const void *object)
{
    const u8 *flags = (const u8 *)object + 0xE8;
    u8 mask = 0x40;

    if (*flags & mask)
        return 1;
    return 0;
}

static inline u8 flag_ea_80(const void *object)
{
    const u8 *flags = (const u8 *)object + 0xEA;
    u8 mask = 0x80;

    if (*flags & mask)
        return 1;
    return 0;
}

static inline u8 flag_eb_04(const void *object)
{
    const u8 *flags = (const u8 *)object + 0xEB;
    u8 mask = 4;

    if (*flags & mask)
        return 1;
    return 0;
}

/* Complete [0x080CD6A8, 0x080CD70A): 98 bytes, 48 instructions. */
u8 func_080CD6A8(const void *object)
{
    if (func_080C8280(object) || flag_e8_40(object) ||
        flag_ea_80(object) || flag_eb_04(object))
        return 1;
    return 0;
}
