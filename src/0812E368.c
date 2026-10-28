#include "ffta.h"

/* Target: complete [0x0812E368, 0x0812E3B0), 72 bytes. */
extern s32 func_080CA580(const void *);
extern u8 func_080CDA34(const void *);
extern u8 func_080CDA64(const void *);
extern u8 func_080CDAAC(const void *);
extern u8 func_080CDAC4(const void *);

s32 func_0812E368(const void *object)
{
    s32 value = func_080CA580(object);

    if (func_080CDA34(object) || func_080CDA64(object))
        value >>= 1;
    if (func_080CDAAC(object))
        value <<= 1;
    if (func_080CDAC4(object))
        value >>= 1;
    return value;
}
