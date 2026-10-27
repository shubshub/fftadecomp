#include "ffta.h"

/* Target: complete [0x080205C8, 0x080205F6), 46 bytes. */
extern u8 func_0801FEB8(const u32 *table, const u32 *resources, u16 index,
                       void *secondary_destination, void *primary_destination,
                       u16 first, u16 last);

u8 func_080205C8(const u32 *table, const u32 *resources, u16 index,
                void *secondary_destination, void *primary_destination)
{
    return func_0801FEB8(table, resources, index, secondary_destination,
                         primary_destination, 0,
                         (u16)(((*table - 4) >> 2) - 1));
}
