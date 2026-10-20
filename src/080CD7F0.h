#ifndef FFTA_080CD7F0_H
#define FFTA_080CD7F0_H

#include "ffta.h"

static inline u8 countdown_a_active(const void *object)
{
    const u8 *flags = (const u8 *)object + 0xEA;
    u8 mask = 0x20;

    if (*flags & mask)
        return 1;
    return 0;
}

static inline u8 countdown_b_active(const void *object)
{
    const u8 *flags = (const u8 *)object + 0xEA;
    u8 mask = 0x40;

    if (*flags & mask)
        return 1;
    return 0;
}

static inline void set_countdown_a_active(void *object, u8 enabled)
{
    u8 *flags = (u8 *)object + 0xEA;
    u8 mask = 0x20;

    *flags &= ~mask;
    if (enabled)
        *flags |= mask;
}

static inline void set_countdown_b_active(void *object, u8 enabled)
{
    u8 *flags = (u8 *)object + 0xEA;
    u8 mask = 0x40;

    *flags &= ~mask;
    if (enabled)
        *flags |= mask;
}

#endif
