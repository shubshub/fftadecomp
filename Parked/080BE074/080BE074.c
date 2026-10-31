#include "ffta.h"

/* Complete target [0x080BE074, 0x080BE1F4): 384 bytes, 185 instructions.
 * f0 b5 4f 46 46 46 c0 b4 05 1c 07 98 09 06 12 06
 * 1b 06 1b 0e 98 46 00 06 00 0e 81 46 0e 0e 17 0e
 * 12 16 85 23 9b 00 e8 18 03 68 09 16 00 29 0e db
 * 10 1c 00 28 0b db 0f 29 09 dc 0f 28 07 dc 00 01
 * 18 18 40 18 01 78 80 20 08 40 00 28 01 d0 00 20
 * 00 e0 01 20 00 28 00 d1 86 e0 86 21 89 00 68 18
 * 01 78 04 20 08 40 00 28 10 d0 28 68 02 68 10 1c
 * f6 30 01 78 30 06 00 16 81 42 75 d1 10 1c f7 30
 * 01 78 38 06 00 16 81 42 6e d1 1f e0 30 06 3a 06
 * 14 16 85 23 9b 00 e9 18 09 68 03 16 84 46 00 2b
 * 11 db 20 1c 00 28 0e db 0f 2b 0c dc 0f 28 0a dc
 * 00 01 08 18 c0 18 00 78 81 21 49 42 08 40 02 28
 * 01 d1 01 20 00 e0 00 20 00 28 01 d0 01 20 4c e0
 * 13 16 85 21 89 00 68 18 04 68 60 46 01 16 00 29
 * 0e db 18 1c 00 28 0b db 0f 29 09 dc 0f 28 07 dc
 * 00 01 20 18 40 18 00 78 00 28 01 d0 01 20 00 e0
 * 00 20 00 28 30 d0 d9 21 49 00 68 18 00 78 00 28
 * 16 d0 28 68 c0 6b 63 46 19 0e 12 0e 8b f0 0c f9
 * 04 1c 28 68 c0 6b 14 4a a9 18 09 78 da 23 5b 00
 * ea 18 12 78 8b f0 00 f9 24 06 00 06 84 42 13 d2
 * d9 20 40 00 29 18 01 20 08 70 0b 49 68 18 06 70
 * da 22 52 00 a8 18 07 70 08 4b e8 18 41 46 01 70
 * 02 32 a8 18 4b 46 03 70 00 20 18 bc 98 46 a1 46
 * f0 bc 02 bc 08 47 00 00 b3 01 00 00 b5 01 00 00
 */

typedef struct {
    u8 unknown_00[0xF6];
    u8 unknown_F6;
    u8 unknown_F7;
} Coordinates080BE074;

typedef struct {
    Coordinates080BE074 *coordinates;
    u8 unknown_04[0x38];
    void *map;
} Actor080BE074;

typedef struct {
    Actor080BE074 *actor;
    u8 unknown_04[0x1AE];
    u8 unknown_1B2;
    u8 unknown_1B3;
    u8 unknown_1B4;
    u8 unknown_1B5;
    u8 unknown_1B6;
    u8 unknown_1B7[0x5D];
    u8 *unknown_214;
    u8 unknown_218;
} State080BE074;

extern s32 func_081493AC(void *map, u8 x, u8 y);

static inline u8 grid_is_open(u8 *grid, s8 x, s8 y)
{
    if (x < 0 || y < 0 || x > 15 || y > 15 ||
        (grid[y * 16 + x] & 0x80))
        return 0;
    return 1;
}

static inline u8 grid_is_two(u8 *grid, s8 x, s8 y)
{
    if (x >= 0 && y >= 0 && x <= 15 && y <= 15 &&
        (grid[y * 16 + x] & ~0x80) == 2)
        return 1;
    return 0;
}

static inline u8 grid_is_nonzero(u8 *grid, s8 x, s8 y)
{
    if (x < 0 || y < 0 || x > 15 || y > 15 || grid[y * 16 + x] == 0)
        return 0;
    return 1;
}

u32 func_080BE074(State080BE074 *state, u8 x, u8 y, u8 next_x, u8 next_y)
{
    if (!grid_is_open(state->unknown_214, x, y))
        return 0;
    if (state->unknown_218 & 4) {
        if (state->actor->coordinates->unknown_F6 != (s8)x ||
            state->actor->coordinates->unknown_F7 != (s8)y)
            return 0;
        return 1;
    }
    if (grid_is_two(state->unknown_214, x, y))
        return 1;
    if (grid_is_nonzero(state->unknown_214, x, y)) {
        if (state->unknown_1B2) {
            s32 value = func_081493AC(state->actor->map, x, y);
            if ((u8)value >= (u8)func_081493AC(state->actor->map,
                                             state->unknown_1B3,
                                             state->unknown_1B4))
                return 0;
        }
        state->unknown_1B2 = 1;
        state->unknown_1B3 = x;
        state->unknown_1B4 = y;
        state->unknown_1B5 = next_x;
        state->unknown_1B6 = next_y;
    }
    return 0;
}
