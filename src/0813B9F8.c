#include "ffta.h"

/* 0x0813B9F8..0x0813BA5C: 100 bytes. */
extern const u16 g_table_08529EE4[];
extern u8 func_080C95D8(u16 id, void *context);
extern u8 func_0813B9B8(void *context);

u16 func_0813B9F8(void *context)
{
    s32 count = 0;
    s32 i;
    u16 id;

    for (i = 0; (id = g_table_08529EE4[i]) != 0xFFFF; ++i) {
        if (func_080C95D8(id + 0x2FF, context))
            ++count;
    }
    if (func_080C95D8(0x36, context))
        ++count;
    else if (func_0813B9B8(context))
        ++count;
    return count;
}
