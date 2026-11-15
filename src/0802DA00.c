#include "ffta.h"

/* The object at 0x02002FC4 as src/0802D7A0.c and src/08063060.c declare it,
   with the index at 0x3C28 of src/08062CA4.c.  Here the ROM forms its address
   as the 0x02000000 block plus 0x2FC4 (0x0802DA1E), so it is a member. */
typedef struct {
    u8 unknown_000[0xC64];
    u16 index;
    u8 unknown_C66[8];
    u8 total;
    u8 count;
    u16 entries[4];
} SelectionState;

typedef struct {
    u8 unknown_0000[0x1F6A];
    u8 row;
    u8 unknown_1F6B[0x2190 - 0x1F6B];
    u8 phase;
    u8 unknown_2191[0x2FC4 - 0x2191];
    SelectionState selection;
} GlobalState;

typedef void (*BufferInitializer)(void *destination, u32 size);

extern GlobalState g_state_02000000;
extern const u16 g_table_08528E1C[][20];
extern BufferInitializer const g_callbacks_0836D4B8[];
extern u8 func_080C9540(u16 bitIndex);

/* Complete target: [0x0802DA00, 0x0802DBA0), 416 bytes, 161 instructions.
 * f0b5474680b40006144c154aa1180a7891008918c900134a89188846050e1248
 * 27181248124966180268301c082114f10dfc104aa318002018700f4960180278
 * 012a00d19ae0022a1ad114203080012018700a496018027090e0000000000002
 * 6a1f00001c8e5208c42f0000b8d43608343c0000333c000090210000323c0000
 * 044aa01800882c280bd02c2804dc2b2810d031e0283c00002d281bd02e2809d0
 * 2ae05320308002482118542017e00000363c0000c7200001391853200880044a
 * b918012008700221013ab818017055e06f0c0000532030800548211824200880
 * 022018700321034aa018017046e00000363c0000323c0000291c481c0006050e
 * 490041440988c7221201b81801801e483c182078013020701c489bf011fd0006
 * 00280fd00021132d00d8291c481c0006050e480040440188154ab81801802078
 * 0130207013489bf0fbfc000600280ed00020132d00d8281c4000404401880e4a
 * b8180180084839180878013008700649781800780130094ab918087008bc9846
 * f0bc01bc004700006f0c000006020000720c000011020000740c00006e0c0000
 */
void func_0802DA00(u8 value)
{
    const u16 *row = g_table_08528E1C[g_state_02000000.row];
    u8 column = value;
    SelectionState *selection = &g_state_02000000.selection;

    g_callbacks_0836D4B8[0](selection->entries, sizeof(selection->entries));
    selection->count = 0;

    if (g_state_02000000.phase == 1)
        return;
    if (g_state_02000000.phase == 2) {
        selection->entries[0] = 0x14;
        selection->count = 1;
        selection->total = selection->count + 1;
        return;
    }

    switch (selection->index) {
    case 0x2C:
        selection->entries[0] = 0x53;
        selection->entries[1] = 0x54;
        selection->count = 2;
        selection->total = selection->count + 1;
        return;
    case 0x2B:
    case 0x2E:
        selection->entries[0] = 0x53;
        selection->count = 1;
        selection->total = selection->count + 1;
        return;
    case 0x2D:
        selection->entries[0] = 0x53;
        selection->entries[1] = 0x24;
        selection->count = 2;
        selection->total = selection->count + 1;
        return;
    }

    selection->entries[0] = row[column++];
    selection->count++;
    if (func_080C9540(0x206)) {
        column = column < 20 ? column : 0;
        selection->entries[1] = row[column++];
        selection->count++;
    }
    if (func_080C9540(0x211)) {
        column = column < 20 ? column : 0;
        selection->entries[2] = row[column];
        selection->count++;
    }
    selection->total = selection->count + 1;
}
