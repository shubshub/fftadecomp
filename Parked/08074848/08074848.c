#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0c];
    u16 *large_second;
    u16 *large_first;
    u16 *small_second;
    u16 *small_first;
    u16 *buffer;
} ResourceContext08074848;

typedef struct {
    u16 *large_tiles;
    u16 *small_tiles;
    u16 *regions[12];
} TileStorage08074848;

extern ResourceContext08074848 *data_03002818;
extern TileStorage08074848 data_03002740;

/* Complete target [0x08074848, 0x080748A8): 96 bytes, 35 instructions. */
void func_08074848(void)
{
    TileStorage08074848 *storage = &data_03002740;
    s32 i;
    u16 **region;
    u16 *buffer;

    for (region = storage->regions, i = 0; i < 12; i++)
        *region++ = 0;
    /* Fixed GBA VRAM tile-storage areas for the two resource planes. */
    storage->large_tiles = (u16 *)0x06007000;
    storage->small_tiles = (u16 *)0x06005800;
    data_03002818->large_first = (u16 *)0x06007000;
    data_03002818->large_second = (u16 *)0x06006000;
    data_03002818->small_first = (u16 *)0x06005800;
    data_03002818->small_second = (u16 *)0x06005000;
    buffer = data_03002818->buffer;
    storage->regions[0] = buffer;
    storage->regions[1] = buffer + 0xfc;
    storage->regions[2] = buffer + 0x18c;
}
