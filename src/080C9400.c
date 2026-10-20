#include "ffta.h"

extern const u8 g_table_085231F4[43][2];

u8 func_080C9400(u8 key)
{
    const u8 (*entry)[2] = g_table_085231F4;
    s32 index;

    for (index = 0; index < 43; index++, entry++) {
        if ((*entry)[1] == key)
            return (*entry)[0];
    }
    return 0;
}
