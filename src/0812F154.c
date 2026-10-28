#include "ffta.h"

/* 0x0812F154..0x0812F17A: 38 bytes. */
extern u8 func_080C8280(const void *);
extern u8 func_080CD914(const void *);

u8 func_0812F154(const void *unit)
{
    if (func_080C8280(unit) || !func_080CD914(unit))
        return 0;
    return 1;
}
