#include "ffta.h"

/* 0x080A8A68..0x080A8A7E: 22 bytes, 10 instructions. */
extern u8 func_080A75BC(void *object, u16 first, u16 second);

u32 func_080A8A68(void *object, u16 first, u16 second)
{
    return func_080A75BC(object, first, second);
}
