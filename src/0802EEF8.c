#include "ffta.h"

typedef struct {
    u8 x;
    u8 unknown_01;
    u8 y;
    u8 unknown_03[4];
    u8 count;
    u8 tile_offset;
    u8 selected;
} ListState;

typedef struct {
    u8 unknown_00[0x14];
    u16 *map;
} Background;

typedef struct ExtendedRequestNode ExtendedRequestNode;

extern ListState *data_0200F444;
extern Background data_03000990;
extern Background data_030008B0;
extern const u8 data_083C4B44[];
extern u16 func_080161A0(u8 x, u8 y, u8 width);
extern ExtendedRequestNode *func_0802DFCC(void);
extern void func_08000BAC(ExtendedRequestNode *entry, u32 first, u32 second,
    u16 count, u16 field_10, u16 field_12, u16 field_14);
extern void func_080157A8(u16 *tilemap, u8 column, u8 row, u8 width,
    u8 height, u8 stride, u16 tile, u8 palette);
extern void func_0802E08C(u32 index, u8 selected);

/* Complete 328-byte selected-list rendering update. */
void func_0802EEF8(void)
{
    s32 i;
    u16 *destination;
    u16 *item;

    for (i = 0; i < data_0200F444->count; ++i) {
        if ((data_0200F444->selected >> i) & 1) {
            item = (u16 *)data_083C4B44;
            destination = data_03000990.map +
                func_080161A0(data_0200F444->x,
                    data_0200F444->y + 2 + i * 2, 32);
            func_08000BAC(func_0802DFCC(), (u32)item,
                (u32)destination, 12, 2, 52, 64);
            item = (u16 *)((u8 *)data_0200F444 + 0x49C + i * 0x68);
            destination = data_030008B0.map +
                func_080161A0(data_0200F444->x + 1,
                    data_0200F444->y + 2 + i * 2, 32);
            func_080157A8(item, 0, 0, 11, 1, 26,
                0x10E + i * 22, 7);
            func_080157A8(item + 12, 0, 0, 11, 1, 26,
                0x10E + (i + data_0200F444->tile_offset) * 22, 8);
            func_08000BAC(func_0802DFCC(), (u32)item,
                (u32)destination, 12, 2, 52, 64);
            func_0802E08C(i, 1);
        }
    }
}
