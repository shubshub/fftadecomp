#include "ffta.h"

/* 0x0801E710..0x0801E952: 578 target bytes, including literal pool. */
typedef struct {
    s16 x;
    s16 height;
    s16 z;
    s16 unknown_06;
} Position0801E710;

extern u8 data_0200F1D0;
extern Position0801E710 data_0200F1A0[3];
extern Position0801E710 data_0200F1B8[3];
extern u16 *func_0801AD38(int);
extern u8 func_0801E630(void);
extern u8 func_0801E648(void);
extern void func_0801C918(int, int, int, s16 *, s16 *, s16 *);

u8 func_0801E710(u16 x, u16 z, u16 height, u8 minimum, u8 width, u8 depth)
{
    u8 result;
    s16 out_x, out_z, out_height;
    s16 current_x, current_z;
    s16 tile_x, tile_z;
    s16 row, column;
    u8 columns, rows;
    u16 (*tiles)[32];
    u16 tile;
    u32 px, py, pz;
    int i;
    int dx, dz;
    int signed_x;

    tiles = (u16 (*)[32])func_0801AD38(0);
    signed_x = (s16)x;
    tile_x = signed_x >> 4;
    tile_z = (s16)z >> 3;
    columns = 1 << (width >> 1);
    if (width == 0) {
        if ((signed_x & 8) && (signed_x & 7))
            columns++;
    } else if (signed_x & 15) {
        columns++;
    }
    rows = 1 << depth;
    if (z & 7)
        rows++;
    result = func_0801E630();
    if (!func_0801E648())
        return result;
    for (row = 0; row < rows; row++) {
        current_z = tile_z + row;
        for (column = 0; column < columns; column++) {
            current_x = tile_x + column;
            if ((u16)current_x > 31 || current_z < 0 || current_z > 63)
                continue;
            tile = tiles[current_z][current_x];
            if (!tile)
                continue;
            px = tile & 31;
            py = (tile & 0x3e0) >> 5;
            pz = (tile & 0x7c00) >> 10;
            func_0801C918(px * 32 + 16, py * 16, pz * 32 + 16,
                         &out_x, &out_z, &out_height);
            if (out_height < (s16)height || minimum >= py)
                continue;
            if (data_0200F1D0 == 0) {
                if (out_height == (s16)height) {
                    if (data_0200F1A0[2].x != px || data_0200F1A0[2].z != pz) {
                        for (i = 0; i <= 1; i++) {
                            dx = data_0200F1A0[i].x - px;
                            if (dx < 0)
                                dx = -dx;
                            dz = data_0200F1A0[i].z - pz;
                            if (dz < 0)
                                dz = -dz;
                            if (dx + dz <= 1 && data_0200F1A0[i].height >= data_0200F1A0[2].height)
                                return result;
                        }
                    }
                }
                for (i = 0; i <= 2; i++) {
                    if (data_0200F1B8[i].height > data_0200F1A0[2].height)
                        goto found;
                }
                for (i = 0; i <= 1; i++) {
                    if (data_0200F1A0[i].x == px && data_0200F1A0[i].z == pz &&
                        data_0200F1A0[i].height > data_0200F1A0[2].height)
                        return result;
                }
            }
found:
            result++;
            return result;
        }
    }
    return result;
}
