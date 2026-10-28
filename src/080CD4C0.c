#include "ffta.h"

typedef struct {
    u8 unknown_00[0x3C];
    u8 value;
} Object080CD4C0;

/* Complete [0x080CD4C0, 0x080CD4D2): 18 bytes, 9 instructions. */
u8 func_080CD4C0(const Object080CD4C0 *object)
{
    u8 value;

    if (object != 0)
        value = object->value;
    else
        value = 0;
    return value;
}
