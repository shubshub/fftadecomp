#include "ffta.h"

// Target 0x0801D130, complete [0x0801D130, 0x0801D2B8), 392 bytes.
typedef struct {
    u8 active;
    u8 mode;
    u8 style;
    u8 palette;
    u8 unknown_04[2];
    u16 tile_base;
    u8 unknown_08[8];
    u8 *destination;
    u8 unknown_14[0x14];
    u8 cells[2 * 16 * 16];
} State0801D130;

typedef struct {
    s16 x;
    s16 y;
} Offset0801D130;

typedef struct {
    Offset0801D130 at[4];
} Offsets0801D130;

extern State0801D130 data_02008168;
extern const Offsets0801D130 data_081498F4;
extern const u8 data_081498F0[];
extern void func_0801CF10(u8 kind, u8 x, u8 y, u8 direction, u8 layer,
                          u16 base_tile, u16 *output);

void func_0801D130(u8 x, u8 y, u8 column, u8 row, u8 *layers, u8 kind)
{
    State0801D130 *state = &data_02008168;
    Offsets0801D130 offsets = data_081498F4;
    u8 direction;

    for (direction = 0; direction < 4; direction++) {
        s32 index;
        u16 tile;
        u8 step;
        u8 *destination;

        switch (direction) {
        case 0:
            index = x + y * 16 + (layers[direction] << 8);
            if ((state->cells[index] >> 6) == kind)
                continue;
            state->cells[index] = (state->cells[index] & 0x3f) | (kind << 6);
            break;
        case 1:
            index = x + y * 16 + (layers[direction] << 8);
            if (((state->cells[index] >> 4) & 3) == kind)
                continue;
            state->cells[index] = (state->cells[index] & 0xcf) | (kind << 4);
            break;
        case 2:
            index = x + y * 16 + (layers[direction] << 8);
            if (((state->cells[index] >> 2) & 3) == kind)
                continue;
            state->cells[index] = (state->cells[index] & 0xf3) | (kind << 2);
            break;
        case 3:
            index = x + y * 16 + (layers[direction] << 8);
            if ((state->cells[index] & 3) == kind)
                continue;
            state->cells[index] = (state->cells[index] & 0xfc) | kind;
            break;
        }

        tile = (state->palette << 12) | state->tile_base;
        step = data_081498F0[state->style];
        if (kind == 2)
            tile += step * 3;

        if (layers[direction] == 0)
            destination = state->destination;
        else
            destination = state->destination + 0x2000;
        destination += (row + offsets.at[direction].y) * 128;
        destination += (column + offsets.at[direction].x) * 2;

        func_0801CF10(kind, x, y, direction, layers[direction], tile,
                      (u16 *)destination);
    }
}
