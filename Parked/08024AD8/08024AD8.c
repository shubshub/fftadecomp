#include "ffta.h"

typedef union {
    u32 word;
    struct {
        u16 value;
        u16 unknown_02;
    } parts;
} Coordinate08024AD8;

typedef struct {
    Coordinate08024AD8 x;
    Coordinate08024AD8 y;
} Position08024AD8;

typedef struct {
    u8 unknown_00[10];
    u8 changed;
    u8 unknown_0b;
    Position08024AD8 current;
    Position08024AD8 previous;
    u8 minimum_x;
    u8 minimum_y;
    u8 maximum_x;
    u8 maximum_y;
} Navigation08024AD8;

extern u8 g_state_02000000[];
extern u16 data_0200F3A4[];
extern u16 data_03000000[];
extern u8 func_0801CC7C(u8 x, u8 y);
extern u32 func_0801CD08(u8 x, u8 y);
extern void func_08141540(u32 sound);

static inline int tile_allows_movement(u8 x, u8 y)
{
    return func_0801CC7C(x, y) && !(func_0801CD08(x, y) & 8);
}

/* 0x08024AD8: directional movement with bounded diagonal fallbacks. */
void func_08024AD8(Navigation08024AD8 *state)
{
    u16 x = state->current.x.parts.value;
    u16 y = state->current.y.parts.value;

    state->changed = 0;
    if (!(g_state_02000000[0x2FC0] & 1)) {
        if (data_0200F3A4[1] & 0x20) {
            if (x > state->minimum_x) {
                int next_x = x - 1;
                if (tile_allows_movement(next_x, y)) {
                    x = next_x;
                } else if (y < state->maximum_y - 1 &&
                           tile_allows_movement(next_x, y + 1)) {
                    x = next_x;
                    y = y + 1;
                } else if (y > state->minimum_y &&
                           tile_allows_movement(next_x, y - 1)) {
                    x = next_x;
                    y = y - 1;
                }
            }
        } else if (data_0200F3A4[1] & 0x10) {
            if (x < state->maximum_x - 1) {
                int next_x = x + 1;
                if (tile_allows_movement(next_x, y)) {
                    x = next_x;
                } else if (y < state->maximum_y - 1 &&
                           tile_allows_movement(next_x, y + 1)) {
                    x = next_x;
                    y = y + 1;
                } else if (y > state->minimum_y &&
                           tile_allows_movement(next_x, y - 1)) {
                    x = next_x;
                    y = y - 1;
                }
            }
        }
        if (data_0200F3A4[1] & 0x80) {
            if (y < state->maximum_y - 1) {
                int next_y = y + 1;
                if (tile_allows_movement(x, next_y)) {
                    y = next_y;
                } else if (x < state->maximum_x - 1 &&
                           tile_allows_movement(x + 1, next_y)) {
                    x = x + 1;
                    y = next_y;
                } else if (x > state->minimum_x &&
                           tile_allows_movement(x - 1, next_y)) {
                    x = x - 1;
                    y = next_y;
                }
            }
        } else if (data_0200F3A4[1] & 0x40) {
            if (y > state->minimum_y) {
                int next_y = y - 1;
                if (tile_allows_movement(x, next_y)) {
                    y = next_y;
                } else if (x < state->maximum_x - 1 &&
                           tile_allows_movement(x + 1, next_y)) {
                    x = x + 1;
                    y = next_y;
                } else if (x > state->minimum_x &&
                           tile_allows_movement(x - 1, next_y)) {
                    x = x - 1;
                    y = next_y;
                }
            }
        }
    } else {
        if (data_0200F3A4[1] & 0x40) {
            if (x > state->minimum_x) {
                int next_x = x - 1;
                if (tile_allows_movement(next_x, y)) {
                    x = next_x;
                } else if (y < state->maximum_y - 1 &&
                           tile_allows_movement(next_x, y + 1)) {
                    x = next_x;
                    y = y + 1;
                } else if (y > state->minimum_y &&
                           tile_allows_movement(next_x, y - 1)) {
                    x = next_x;
                    y = y - 1;
                }
            }
        } else if (data_0200F3A4[1] & 0x80) {
            if (x < state->maximum_x - 1) {
                int next_x = x + 1;
                if (tile_allows_movement(next_x, y)) {
                    x = next_x;
                } else if (y < state->maximum_y - 1 &&
                           tile_allows_movement(next_x, y + 1)) {
                    x = next_x;
                    y = y + 1;
                } else if (y > state->minimum_y &&
                           tile_allows_movement(next_x, y - 1)) {
                    x = next_x;
                    y = y - 1;
                }
            }
        }
        if (data_0200F3A4[1] & 0x20) {
            if (y < state->maximum_y - 1) {
                int next_y = y + 1;
                if (tile_allows_movement(x, next_y)) {
                    y = next_y;
                } else if (x < state->maximum_x - 1 &&
                           tile_allows_movement(x + 1, next_y)) {
                    x = x + 1;
                    y = next_y;
                } else if (x > state->minimum_x &&
                           tile_allows_movement(x - 1, next_y)) {
                    x = x - 1;
                    y = next_y;
                }
            }
        } else if (data_0200F3A4[1] & 0x10) {
            if (y > state->minimum_y) {
                int next_y = y - 1;
                if (tile_allows_movement(x, next_y)) {
                    y = next_y;
                } else if (x < state->maximum_x - 1 &&
                           tile_allows_movement(x + 1, next_y)) {
                    x = x + 1;
                    y = next_y;
                } else if (x > state->minimum_x &&
                           tile_allows_movement(x - 1, next_y)) {
                    x = x - 1;
                    y = next_y;
                }
            }
        }
    }
    if (data_03000000[2])
        data_03000000[2] = 0;
    if (state->current.x.parts.value != x || state->current.y.parts.value != y) {
        func_08141540(0x6C);
        state->changed = 1;
    }
    state->previous = state->current;
    state->current.x.parts.value = x;
    state->current.y.parts.value = y;
}
