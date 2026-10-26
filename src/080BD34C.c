#include "ffta.h"

/* 0x080BD34C..0x080BD35A: 14 bytes, 6 Thumb instructions. */
extern u8 func_080BD1EC(void *context);

u32 func_080BD34C(void *context)
{
    return func_080BD1EC(context);
}
