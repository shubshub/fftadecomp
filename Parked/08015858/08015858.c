#include "ffta.h"

/* 0x08015858..0x08015C90: 1080 bytes. */
typedef struct __attribute__((packed)) {
    u16 id : 10;
    u16 unknown_0a : 6;
    u8 flags;
} TileResource;

typedef struct {
    TileResource *current;
    u32 unknown_04;
    u32 unknown_08;
    u16 id;
    u8 unknown_0e[2];
    u8 selection;
    u8 secondary;
    u8 mode;
    u8 unknown_13[0xA1];
    u8 special;
} TileSelection;

extern TileSelection g_state_020020D0;
extern u8 func_080C9540(u16 bitIndex);
extern u32 func_080CE4DC(u16 id, u32 field);

#define CURRENT_TILE_RESOURCE \
    (g_state_020020D0.current \
        ? g_state_020020D0.current->id : g_state_020020D0.id)

void func_08015858(u16 *buffer, u8 x, u8 y, u8 width, u8 height,
                   u8 stride, u16 firstTile, u8 palette)
{
    u16 *row;
    u16 tile;
    u16 offset;
    u16 column;
    u16 line;
    s32 i;
    u16 rowStep;
    u32 alternate = 0;

    offset = stride * y + x;
    firstTile += palette << 12;
    rowStep = stride * 2;
    row = buffer + offset;
    tile = firstTile + 4;
    for (column = 2; column < width; column++) {
        row[column] = tile++;
        (row + stride)[column] = tile++;
    }

    if (!(g_state_020020D0.mode == 4 && g_state_020020D0.special)
        && (func_080C9540(CURRENT_TILE_RESOURCE + 0x2FF)
            || (CURRENT_TILE_RESOURCE == 0x1A && func_080C9540(0x36)))) {
        {
            s32 decoration;
            decoration = (s16)0xD08E;
            for (i = 5; i >= 0; i--)
                (row + width - 6)[i] = decoration--;
        }
    }

    if (!(g_state_020020D0.mode == 4 && g_state_020020D0.special)) {
        {
            s32 decoration;
            decoration = (s16)0xD084;
            for (i = 3; i >= 0; i--)
                (row + stride - 5 + width)[i] = decoration--;
        }
        (row + stride)[width - 1] = 0xD01E
            + func_080CE4DC(CURRENT_TILE_RESOURCE, 4);
    }

    row += rowStep;
    for (column = 0; column < width; column++)
        row[column] = 0xC050;
    row[-1] = 0xC051;
    row[width] = 0xC451;

    if (g_state_020020D0.mode != 3) {
        row += (height - 2) * rowStep;
        {
            s32 decoration;
            decoration = (s16)0xD087;
            for (i = 2; i >= 0; i--)
                (row + stride - 6 + width)[i] = decoration--;
        }
        (row + stride)[width - 3] = 0xD01F + g_state_020020D0.selection;
        (row + stride)[width - 2] = 0xD088;
        (row + stride)[width - 1] = 0xD01E + g_state_020020D0.secondary;
    }

    row = buffer + (u16)(stride * y + x) + 3 * stride;
    if (func_080CE4DC(CURRENT_TILE_RESOURCE, 2) == 3) {
        if (g_state_020020D0.selection == 1)
            alternate = 1;
    } else if (g_state_020020D0.selection == 2) {
        alternate = 1;
    }

    if (alternate) {
        for (line = 1; line < height - 3; line++) {
            for (column = 0; column < width; column++) {
                row[column] = tile++;
                (row + stride)[column] = tile++;
            }
            row += rowStep;
        }
        for (column = 0; column < width; column++)
            row[column] = 0;
        row += stride;
        for (column = 0; column < width; column++) {
            row[column] = tile++;
            (row + stride)[column] = tile++;
        }
    } else {
        for (line = 1; line < height - 1; line++) {
            for (column = 0; column < width; column++) {
                row[column] = tile++;
                (row + stride)[column] = tile++;
            }
            row += rowStep;
        }
    }
}
