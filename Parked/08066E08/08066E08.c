#include "ffta.h"

/* 0x08066E08..0x08066E9E: 150 bytes. */
typedef struct {
    u8 unknown_00[0x14];
    u16 *tiles;
} TileSurface;

typedef struct {
    u8 unknown_00[8];
    u8 mode;
    u8 unknown_09[5];
    u8 initialized;
    u8 unknown_0f[0x15];
    u8 control_state[1];
} MenuContext;

extern TileSurface data_03000990;
extern TileSurface data_030008B0;
extern u16 func_080161A0(u32 x, u32 y, u32 width);
extern u32 func_08017180(void *state);

u8 func_08066E08(MenuContext *context)
{
    if (context->mode == 4 && !context->initialized) {
        u16 *row = data_03000990.tiles + func_080161A0(1, 0x0B, 0x20);
        u16 *last = row + 0xE0;
        u16 *tiles;
        s32 x;
        s32 y;

        do {
            for (x = 0x1B; x >= 0; --x)
                row[x] = 0;
            row += 0x20;
        } while (row <= last);
        tiles = data_030008B0.tiles + func_080161A0(1, 0x0B, 0x20);
        for (y = 0; y < 8; ++y)
            for (x = 0x1B; x >= 0; --x)
                tiles[y * 0x20 + x] = 0;
        context->initialized = 1;
        return 0;
    }
    return func_08017180(context->control_state);
}
