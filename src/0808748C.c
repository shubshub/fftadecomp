#include "ffta.h"

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

typedef struct {
    u8 unknown_00[0x18];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 stride;
} TileBuffer;

void func_0808748C(TileBuffer *source, TileBuffer *destination,
                   TilePoint origin, TileRect rectangle)
{
    s32 row;
    s32 column;

    for (row = 0; row < rectangle.height; row++) {
        u16 *source_first = source->first_plane + origin.x
            + (origin.y + row) * source->stride;
        u16 *source_second = source->second_plane + origin.x
            + (origin.y + row) * source->stride;
        u16 *destination_first = destination->first_plane + rectangle.x
            + (rectangle.y + row) * destination->stride;
        u16 *destination_second = destination->second_plane + rectangle.x
            + (rectangle.y + row) * destination->stride;

        for (column = 0; column < rectangle.width; column++) {
            destination_first[column] = source_first[column];
            destination_second[column] = source_second[column];
        }
    }
}
