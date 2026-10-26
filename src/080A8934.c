#include "ffta.h"

extern u32 func_080A7138(void *object, u32 mode);

/* 0x080A8934..0x080A8940: 12 bytes. */
u32 func_080A8934(void *object)
{
    return func_080A7138(object, 0);
}
