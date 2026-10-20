#include "ffta.h"

void func_080CD544(void *object, u8 index)
{
    u8 *record = object;

    if (record != 0) {
        u8 *flags = record + 0x40;

        flags[index] |= 0x80;
    }
}
