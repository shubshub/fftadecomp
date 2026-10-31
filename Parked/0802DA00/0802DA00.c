#include "ffta.h"

typedef struct {
    u8 unknown_000[0xC64];
    u16 key;
    u8 unknown_C66[8];
    u8 status;
    u8 count;
    u16 values[4];
} Section0802DA00;

typedef struct {
    u8 unknown_0000[0x1F6A];
    u8 row;
    u8 unknown_1F6B[0x2190 - 0x1F6B];
    u8 branch;
    u8 unknown_2191[0x2FC4 - 0x2191];
    Section0802DA00 section;
} GlobalState0802DA00;

typedef void (*RegionInitializer0802DA00)(void *destination, u32 size);

extern GlobalState0802DA00 g_state_02000000;
extern const u16 g_table_08528E1C[];
extern RegionInitializer0802DA00 g_callbacks_0836D4B8[];
extern u8 func_080C9540(u16 bitIndex);

/* Complete target [0802DA00,0802DBA0): 416 bytes, 161 instructions.
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
void func_0802DA00(u8 entry)
{
    const u16 *row = g_table_08528E1C + g_state_02000000.row * 20;
    Section0802DA00 *section = &g_state_02000000.section;
    u16 *values = section->values;

    g_callbacks_0836D4B8[0](values, sizeof(section->values));
    section->count = 0;

    if (g_state_02000000.branch == 1)
        return;
    if (g_state_02000000.branch == 2) {
        values[0] = 0x14;
        section->count = 1;
        section->status = 2;
        return;
    }

    switch (section->key) {
    case 0x2C:
        values[0] = 0x53;
        values[1] = 0x54;
        section->count = 2;
        section->status = 3;
        return;
    case 0x2B:
    case 0x2E:
        values[0] = 0x53;
        section->count = 1;
        section->status = 2;
        return;
    case 0x2D:
        values[0] = 0x53;
        values[1] = 0x24;
        section->count = 2;
        section->status = 3;
        return;
    }

    values[0] = row[entry++];
    section->count++;
    if (func_080C9540(0x206)) {
        if (entry > 19)
            entry = 0;
        values[1] = row[entry++];
        section->count++;
    }
    if (func_080C9540(0x211)) {
        if (entry > 19)
            entry = 0;
        values[2] = row[entry];
        section->count++;
    }
    section->status = section->count + 1;
}
