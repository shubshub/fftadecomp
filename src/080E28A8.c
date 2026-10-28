#include "ffta.h"

/* 0x080E28A8..0x080E28C4: 28 bytes. */
extern u16 func_08005BAC(const void *object);

int func_080E28A8(const void *object)
{
    u16 value = func_08005BAC(object);

    if (value > 0xFF || value == 2)
        return 1;
    return 0;
}
