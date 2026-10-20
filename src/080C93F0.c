#include "ffta.h"

extern const u8 g_table_085231F4[43][2];

u8 func_080C93F0(u8 index)
{
    const u8 *entry = g_table_085231F4[index];

    return entry[1];
}
