#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u16 *tiles;
} TileMap08066E08;

typedef struct {
    u16 *primary;
    u16 *secondary;
    u8 unknown_08[8];
    u8 x;
    u8 y;
    u8 outer_width;
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
    s16 expected_width;
    s16 expected_height;
} TileRegion08066E08;

typedef struct {
    u8 unknown_00[8];
    u8 mode;
    u8 unknown_09[5];
    u8 counter;
    u8 unknown_0f[0x15];
    TileRegion08066E08 region;
} MenuContext08066E08;

extern TileMap08066E08 data_03000990;
extern TileMap08066E08 data_030008B0;
extern u16 func_080161A0(u8 x, u8 y, u8 width);
extern u8 func_08017180(TileRegion08066E08 *region);

/* Complete target [0x08066E08, 0x08066E9E): 150 bytes, 68 instructions. */
u8 func_08066E08(MenuContext08066E08 *context)
{
    u16 *destination;
    s32 row;
    s32 column;

    if (context->mode == 4 && context->counter == 0) {
        destination = data_03000990.tiles + func_080161A0(1, 11, 32);
        for (row = 0; row < 8; row++) {
            for (column = 0; column < 28; column++)
                destination[column + row * 32] = 0;
        }

        destination = data_030008B0.tiles + func_080161A0(1, 11, 32);
        for (row = 0; row < 8; row++) {
            for (column = 0; column < 28; column++)
                destination[column + row * 32] = 0;
        }
        context->counter = 1;
        return 0;
    }
    return func_08017180(&context->region);
}
