#include "ffta.h"

extern u8 g_state_020020D0[];

/* 0x08016344 - 540 bytes, including literal pools. */
void func_08016344(u16 *tiles, u8 width, u8 height, u16 flags,
                   u8 stride, u16 tile, u8 palette)
{
    u16 last_column;
    u16 last_row;
    u16 base = tile;
    s32 i;

    if (width <= 1 || height <= 1)
        return;

    last_column = width - 1;
    last_row = (height - 1) * stride;
    base += palette << 12;

    if (flags & 0x40) {
        if (flags & 0x200) {
            tiles[stride] = base + 0x804;
        } else {
            tiles[0] = base;
            tiles[stride] = base + 2;
        }
    } else {
        tiles[0] = base + 1;
        tiles[stride] = base + 3;
    }

    if (flags & 0x80) {
        if (flags & 0x200) {
            (tiles + last_column)[stride] = base + 0xc04;
        } else {
            tiles[last_column] = base + 0x400;
            (tiles + last_column)[stride] = base + 0x402;
        }
    } else {
        tiles[last_column] = base + 1;
        (tiles + last_column)[stride] = base + 3;
    }

    if (flags & 0x200) {
        for (i = 1; i < last_column; i++)
            (tiles + stride)[i] = base + 0x805;
    } else {
        for (i = 1; i < last_column; i++) {
            tiles[i] = base + 1;
            (tiles + stride)[i] = base + 3;
        }
    }

    if (height > 2) {
        if (flags & 0x40)
            tiles[last_row] = base + 4;
        else
            tiles[last_row] = base + 5;

        if (flags & 0x80)
            (tiles + last_row)[last_column] = base + 0x404;
        else
            (tiles + last_row)[last_column] = base + 5;

        for (i = 1; i < last_column; i++)
            (tiles + last_row)[i] = base + 5;

        if (flags & 0x100) {
            u16 offset;

            base = tile + 0xd000;
            offset = stride * 2;

            if ((flags & 0xc0) == 0x80)
                offset += last_column;
            if (g_state_020020D0[0xae] != 0 && height > g_state_020020D0[0xae])
                height = g_state_020020D0[0xae];
            if (height != 0 && !(height & 1))
                height--;

            for (i = 2; i < height - 1; i += 2) {
                tiles[offset] = base + 6;
                (tiles + offset)[stride] = base + 7;
                offset += stride * 2;
            }
        }
    }
}
