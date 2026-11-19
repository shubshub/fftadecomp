#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u8 flags;
    u8 status;
    u16 unit;
    u16 column;
    u16 row;
    s16 x;
    s16 y;
    u8 unknown_0E[6];
} Slot080725B8;

/* agbcc gives every struct 4-byte alignment, so the 20-byte slots start at
 * 0x9EC, as src/08071378.c lays them out; flags is at 0x9EE (src/08072B74.c). */
typedef struct {
    u8 unknown_000[0x95C];
    u8 count;
    u8 unknown_95D[0x5D];
    u8 order[24];
    u8 unknown_9D2[0x1A];
    Slot080725B8 slots[24];
} State080725B8;

/* Field names follow src/0802C270.c and src/08071DC8.c. */
typedef struct {
    u8 unknown_00[9];
    u8 level;
    u8 unknown_0A[0x10];
    u16 first;
    u8 unknown_1C[2];
    u16 second;
    u8 unknown_20[0xB6];
    u16 value;
    u8 unknown_D8[0x30];
} Unit080725B8;

typedef struct {
    u8 unknown_00[0x80];
    Unit080725B8 units[24];
} UnitTable080725B8;

extern State080725B8 *data_03002818;
extern UnitTable080725B8 g_state_02000000;
extern u8 g_state_020020D0[];
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_08035678(u16 value, u16 *destination, u32 count, u16 step);
extern void func_08035A68(u16 *destination, u16 digits, u32 value, u16 attributes);

/*
 * Complete target [0x080725B8, 0x08072B74), 1468 bytes, 721 instructions.
 *
 * Each slot's label goes at its tile column and row, the pixel position over
 * eight held as u16 (lsls/lsrs #16 at 0x080725EA and 0x080725FA, and in the
 * first loop of every case).  The number beside it is placed from int x and
 * y, which the ROM never narrows (0x08072706, 0x08072712).
 */
void func_080725B8(int clear)
{
    if (clear == 1) {
        s32 i;

        for (i = 0; i < data_03002818->count; i++) {
            u16 col = data_03002818->slots[i].x >> 3;
            u16 row = (data_03002818->slots[i].y >> 3) + 5;

            func_08035678(0, func_0808B8E4(0, 1, col, row), 6, 0);
        }
    } else {
        s32 i;
        u16 *dst;
        u16 tile;
        u16 palette;
        s32 value;
        s32 digits;
        s32 x;
        s32 y;
        u8 n;

        palette = 15;
        switch (g_state_020020D0[0x15]) {
        case 0:
            tile = 0xD0BF;
            for (i = 0; i < data_03002818->count; i++) {
                u16 col = data_03002818->slots[i].x >> 3;
                u16 row = (data_03002818->slots[i].y >> 3) + 5;

                dst = func_0808B8E4(0, 1, col, row);
                func_08035678(0, dst, 6, 0);
                func_08035678(tile, dst, 2, 1);
            }
            for (i = 0; i < data_03002818->count; i++) {
                n = data_03002818->order[i];
                x = (data_03002818->slots[i].x >> 3) + 2;
                y = (data_03002818->slots[i].y >> 3) + 5;
                func_08035A68(func_0808B8E4(0, 1, x, y), 2,
                              data_03002818->slots[n].status, palette << 12);
            }
            break;
        case 1:
            tile = 0xF05E;
            for (i = 0; i < data_03002818->count; i++) {
                u16 col = data_03002818->slots[i].x >> 3;
                u16 row = (data_03002818->slots[i].y >> 3) + 5;

                dst = func_0808B8E4(0, 1, col, row);
                func_08035678(0, dst, 6, 0);
                func_08035678(tile, dst, 2, 1);
            }
            for (i = 0; i < data_03002818->count; i++) {
                x = (data_03002818->slots[i].x >> 3) + 2;
                y = (data_03002818->slots[i].y >> 3) + 5;
                func_08035A68(func_0808B8E4(0, 1, x, y), 2,
                              g_state_02000000.units[data_03002818->slots[i].unit].level,
                              palette << 12);
            }
            break;
        case 2:
            tile = 0xD052;
            for (i = 0; i < data_03002818->count; i++) {
                u16 col = data_03002818->slots[i].x >> 3;
                u16 row = (data_03002818->slots[i].y >> 3) + 5;

                dst = func_0808B8E4(0, 1, col, row);
                func_08035678(0, dst, 6, 0);
                func_08035678(tile, dst, 2, 1);
            }
            for (i = 0; i < data_03002818->count; i++) {
                value = g_state_02000000.units[data_03002818->slots[i].unit].first;
                digits = value < 100 ? 2 : 3;
                x = (data_03002818->slots[i].x >> 3) + 2;
                y = (data_03002818->slots[i].y >> 3) + 5;
                func_08035A68(func_0808B8E4(0, 1, x, y), digits, value, palette << 12);
            }
            break;
        case 3:
            tile = 0xE054;
            for (i = 0; i < data_03002818->count; i++) {
                u16 col = data_03002818->slots[i].x >> 3;
                u16 row = (data_03002818->slots[i].y >> 3) + 5;

                dst = func_0808B8E4(0, 1, col, row);
                func_08035678(0, dst, 6, 0);
                func_08035678(tile, dst, 2, 1);
            }
            for (i = 0; i < data_03002818->count; i++) {
                value = g_state_02000000.units[data_03002818->slots[i].unit].second;
                digits = value < 100 ? 2 : 3;
                x = (data_03002818->slots[i].x >> 3) + 2;
                y = (data_03002818->slots[i].y >> 3) + 5;
                func_08035A68(func_0808B8E4(0, 1, x, y), digits, value, palette << 12);
            }
            break;
        case 4:
            tile = 0xD056;
            for (i = 0; i < data_03002818->count; i++) {
                u16 col = data_03002818->slots[i].x >> 3;
                u16 row = (data_03002818->slots[i].y >> 3) + 5;

                dst = func_0808B8E4(0, 1, col, row);
                func_08035678(0, dst, 6, 0);
                func_08035678(tile, dst, 2, 1);
            }
            for (i = 0; i < data_03002818->count; i++) {
                x = (data_03002818->slots[i].x >> 3) + 2;
                y = (data_03002818->slots[i].y >> 3) + 5;
                func_08035A68(func_0808B8E4(0, 1, x, y), 2,
                              g_state_02000000.units[data_03002818->slots[i].unit].value,
                              palette << 12);
            }
            break;
        }
    }
}

