#include "ffta.h"

/* Complete [0x0802ED88, 0x0802EEF8): 368 bytes, 162 instructions, including
 * the six-word literal pool at 0x0802EEE0.
 * f0b557464e464546e0b484b00020814693e00968487a4a461041012210404a449246002800d187e0
 * 68204a464243101c494a80184a465500484b091833221888088002330231013a002af8da68204c46
 * 444341496018424a11684018804608788978023549190906090e2022e7f7d4f93c490004c00b4969
 * 0f18fff7e3f802210091342201924021029141463a1c1a23d1f7c8fe344aa418314801686418a046
 * 087801300006000e897849190906090e2022e7f7b1f92d490004c00b49690f18012100911a220192
 * 162648467043872149000d1c40190004000c0290092403944046002100220b23e6f79afc40461830
 * 012200921a210191194a1168097a4944714349190904090c02910394002100220b23e6f785fcfff7
 * 95f802210091342201924021029141463a1c1a23d1f77afe48460021fff7e6f8d14609490868c079
 * 814500da65e704b038bc9846a146aa46f0bc01bc004700003c060000ac4b3c0844f4000290090003
 * 9c040000b0080003
 */

/* x and y are halfwords: func_0802FC74 reads x with ldrh at 0x0802FE1C, and
 * src/0802E3E0.c and src/0802E68C.c declare the same layout, rows included. */
typedef struct {
    u16 x;
    u16 y;
    u8 unknown_04[3];
    u8 count;
    u8 tile_offset;
    u8 selected;
    u8 unknown_0A[0x49C - 0x0A];
    u16 rows[8][52];
} ListState;

typedef struct {
    u8 unknown_00[0x14];
    u16 *map;
} Background;

typedef struct ExtendedRequestNode ExtendedRequestNode;

extern ListState *data_0200F444;
extern Background data_03000990;
extern Background data_030008B0;
extern const u16 data_083C4BAC[];
extern u16 func_080161A0(u8 x, u8 y, u8 width);
extern ExtendedRequestNode *func_0802DFCC(void);
extern void func_08000BAC(ExtendedRequestNode *entry, u32 first, u32 second,
    u16 count, u16 field_10, u16 field_12, u16 field_14);
extern void func_080157A8(u16 *tilemap, u8 column, u8 row, u8 width,
    u8 height, u8 stride, u16 tile, u8 palette);
extern void func_0802E08C(u32 index, u8 selected);

void func_0802ED88(void)
{
    s32 i;
    s32 j;
    u16 *destination;
    u16 *item;

    for (i = 0; i < data_0200F444->count; ++i) {
        if ((data_0200F444->selected >> i) & 1) {
            destination = data_0200F444->rows[i + 4];
            for (j = 0; j < 52; ++j)
                destination[j] = data_083C4BAC[j];
            item = data_0200F444->rows[i + 4];
            destination = data_03000990.map +
                func_080161A0(data_0200F444->x,
                    data_0200F444->y + 2 + i * 2, 32);
            func_08000BAC(func_0802DFCC(), (u32)item,
                (u32)destination, 26, 2, 52, 64);
            item = data_0200F444->rows[i];
            destination = data_030008B0.map +
                func_080161A0(data_0200F444->x + 1,
                    data_0200F444->y + 2 + i * 2, 32);
            func_080157A8(item, 0, 0, 11, 1, 26,
                0x10E + i * 22, 9);
            func_080157A8(item + 12, 0, 0, 11, 1, 26,
                0x10E + (i + data_0200F444->tile_offset) * 22, 9);
            func_08000BAC(func_0802DFCC(), (u32)item,
                (u32)destination, 26, 2, 52, 64);
            func_0802E08C(i, 0);
        }
    }
}
