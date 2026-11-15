#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 stride;
    u8 unknown_29[0x23];
} TileRenderer;

typedef struct {
    u8 unknown_0000[0x1cec];
    s16 value_1cec;
    s16 value_1cee;
    s16 value_1cf0;
    s16 value_1cf2;
    s16 value_1cf4;
    s16 value_1cf6;
} ComparisonState;

extern TileRenderer data_030009E0[];
extern ComparisonState *data_03002818;
extern void func_080CA2E8(void *object);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_080899AC(u32 address, u16 stride, u16 base, u16 value,
                          u16 digits, u16 alignment, u16 attributes);
extern s32 func_080CA394(void *object);
extern s32 func_080CA610(void *object);
extern s32 func_080CA5C4(void *object);

/* 0x08075FA8..0x0807614C: 420 bytes, 173 instructions.
 * value_1cf2, value_1cf4 and value_1cf6 are the halfwords func_08080DB4
 * (src/08080DB4.c) stores from the same three functions called here. */
void func_08075FA8(void *object, s32 neutral)
{
    s16 change;
    u16 tile;

    func_080CA2E8(object);

    change = func_080CA394(object) - data_03002818->value_1cf2;
    if (neutral)
        tile = 0xd000;
    else if (change < 0)
        tile = 0xa000;
    else if (change > 0)
        tile = 0x8000;
    else
        tile = 0xd000;
    func_080899AC((u32)func_0808B8E4(3, 1, 6, 1), data_030009E0[3].stride, 100,
                  change + data_03002818->value_1cec, 1, 0, tile);

    change = func_080CA610(object) - data_03002818->value_1cf4;
    if (neutral)
        tile = 0xd000;
    else if (change < 0)
        tile = 0xa000;
    else if (change > 0)
        tile = 0x8000;
    else
        tile = 0xd000;
    func_080899AC((u32)func_0808B8E4(0, 1, 6, 9), 0x20, 120,
                  change + data_03002818->value_1cee, 1, 0, tile);

    change = func_080CA5C4(object) - data_03002818->value_1cf6;
    if (neutral)
        tile = 0xd000;
    else if (change < 0)
        tile = 0xa000;
    else if (change > 0)
        tile = 0x8000;
    else
        tile = 0xd000;
    func_080899AC((u32)func_0808B8E4(3, 1, 12, 2), data_030009E0[3].stride, 120,
                  change + data_03002818->value_1cf0, 3, 0, tile);
}
