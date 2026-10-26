#include "ffta.h"

/* 0x08089E1C..0x08089EB4: 152 bytes. */
typedef struct {
    u8 unknown_00[0x1C];
    u16 *tiles;
    u8 unknown_20[8];
    u8 stride;
} TileSurface;

typedef struct {
    s8 x;
    s8 y;
} TilePoint;

typedef struct {
    s8 x;
    s8 y;
    s8 width;
    s8 height;
} TileRect;

void func_08089E1C(TileSurface *source, TileSurface *destination,
                   TilePoint point, TileRect rect)
{
    s32 row;

    for (row = 0; row < rect.height; ++row) {
        const u16 *source_row = source->tiles + point.x
            + (point.y + row) * source->stride;
        u16 *destination_row = destination->tiles + rect.x
            + (rect.y + row) * destination->stride;
        s8 width = rect.width;

        if (width > 0) {
            s32 remaining = width;
            do {
                *destination_row++ = *source_row++;
            } while (--remaining);
        }
    }
}
