#ifndef FFTA_080CD774_H
#define FFTA_080CD774_H

#include "ffta.h"

static inline void set_first_active(void *object, u8 enabled)
{
    u8 *flags = (u8 *)object + 0xEA;
    u8 mask = 0x20;

    *flags &= ~mask;
    if (enabled)
        *flags |= mask;
}

static inline void set_second_active(void *object, u8 enabled)
{
    u8 *flags = (u8 *)object + 0xEA;
    u8 mask = 0x40;

    *flags &= ~mask;
    if (enabled)
        *flags |= mask;
}

#endif
