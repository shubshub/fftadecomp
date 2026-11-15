#include "ffta.h"

/* 0x080DE1F0..0x080DE1FE: 14 bytes. */
extern u32 func_08099C64(const void *owner);

u8 func_080DE1F0(void *object)
{
    return func_08099C64(object);
}
