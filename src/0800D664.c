#include "ffta.h"

/* 0x0800D664..0x0800D73C: 216 bytes. */
typedef struct {
    u32 tile : 16;
    u32 layer : 8;
    u32 palette : 8;
    u32 x : 8;
    u32 y : 8;
    u32 unknown_30 : 16;
} PackedEntry;

typedef struct {
    u16 tile;
    u8 unknown_02[2];
    u8 layer;
    u8 palette;
    u8 x;
    u8 y;
    u8 unknown_08[20];
} Entry28;

extern Entry28 *func_0800C614(void *object);

void func_0800D664(void *object, u8 mode, u8 index, u8 x,
                   u8 y, u8 palette, u16 tile, u8 layer)
{
    PackedEntry packed;
    Entry28 *entry = 0;
    const u8 *bytes;

    switch (mode) {
    case 0:
        entry = func_0800C614(object);
        break;
    case 1:
        entry = func_0800C614(object) + index;
        break;
    case 2:
        entry = func_0800C614(object) + index;
        break;
    }
    packed.tile = tile;
    packed.palette = palette;
    packed.x = x;
    packed.y = y;
    packed.layer = layer;
    bytes = (const u8 *)&packed;
    entry->tile = *(const u16 *)bytes;
    entry->layer = bytes[2];
    entry->palette = bytes[3];
    entry->x = bytes[4];
    entry->y = bytes[5];
}
