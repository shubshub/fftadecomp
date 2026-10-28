#include "ffta.h"

/* 0x080CB48C..0x080CB4A4: 24 bytes, 11 Thumb instructions. */
extern u8 func_080CAE2C(void *object, u16 entry, u8 slot, u8 mode);

u32 func_080CB48C(void *object, u16 entry, u8 slot)
{
    return func_080CAE2C(object, entry, slot, 0);
}
