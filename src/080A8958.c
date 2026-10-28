#include "ffta.h"

/* 0x080A8958..0x080A8966: 14 bytes, 6 instructions. */
extern u8 func_080A7218(void *object);

u32 func_080A8958(void *object)
{
    return func_080A7218(object);
}
