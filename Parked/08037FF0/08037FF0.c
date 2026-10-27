#include "ffta.h"

/* Target: complete [0x08037FF0, 0x08038014), 36 bytes. */
typedef struct {
    u16 *primary;
    u16 *secondary;
    u8 unknown_08[8];
    u8 x;
    u8 y;
    u8 outerWidth;
    u8 unknown_13;
    u16 value;
    u8 stride;
    u8 mode;
    u16 first;
    u16 last;
    u8 flags;
    u8 unknown_1D[2];
    u8 alignment;
    u16 width;
    u16 height;
    s16 expectedWidth;
    s16 expectedHeight;
} TileRegion;

typedef struct {
    TileRegion region;
    u8 unknown_28[0xA4];
} RegionRecord08037FF0;

extern u8 *g_state_03002810;
extern u8 func_08017180(TileRegion *region);

u8 func_08037FF0(u32 index)
{
    u32 address = (u32)g_state_03002810 + index * sizeof(RegionRecord08037FF0);
    TileRegion *region = (TileRegion *)(address + 0x9A0);

    return func_08017180(region);
}
