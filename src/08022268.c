#include "ffta.h"

/* 0x08022268..0x08022298: 48 bytes. */
extern u8 func_080C8240(void *object);
extern u8 func_080CB65C(void *object, u8 mode);
extern u16 func_080CB750(void *object);

u16 func_08022268(void *object, u8 *output)
{
    if (func_080C8240(object) != 0)
        *output = func_080CB65C(object, 0);
    else
        *output = func_080CB65C(object, 1);
    return func_080CB750(object);
}
