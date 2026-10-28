#include "ffta.h"

/* 0x080372FC..0x08037398: 156 bytes. */
typedef struct {
    u8 tile;
    u8 unknown_01[3];
} IconRecord;

typedef struct {
    u32 unknown_00;
    void *map;
} TileDisplay;

extern const IconRecord data_08391CA4[];
extern TileDisplay data_03000E30;
extern const u8 data_08950000[];
extern const u8 data_08950F4C[];
extern void func_0804C598(void *map, u32 layer, u8 tile, u8 x, u8 y,
                          u32 first, u32 second, const void *tiles,
                          const void *palette, u32 style);

static inline u8 icon_tile(u8 icon)
{
    return data_08391CA4[icon - 1].tile + 0x19;
}

void func_080372FC(u32 x, u32 y, u8 icon, u8 layer)
{
    if (icon != 0) {
        u8 tile = icon_tile(icon);
        func_0804C598(data_03000E30.map, layer + 3, tile, x, y,
                      0, 0, data_08950000, data_08950F4C, 0x52);
    } else {
        func_0804C598(data_03000E30.map, layer + 3, 1, x, y,
                      0, 0, data_08950000, data_08950F4C, 0x30);
    }
}
