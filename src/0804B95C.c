#include "ffta.h"

/* Complete [0x0804B95C, 0x0804BB10): 436 bytes, 179 instructions, seventeen
 * literal words in five pools.
 * f0b557464e464546e0b4061c0b1c0d4d75600021317371730f20b073f073002209483082
 * b274b1821020b075f2758c2189007018b06100229146012b06d0022b68d0a9e080665208
 * ad010000002398460f48104909188a4600278c229200b4180b4838180c4bc11808780028
 * 40d000010a49401802881001094bc1188878002810d0c5235b00181c89784018051c0ae0
 * 000000020a2b0000082b000014125208a4fa51080025174950180004000c031c1549164a
 * 9818800040180268514608880121002800d000214846208061804146a180a2600e4a9818
 * a0810023a373281c7ff0aeff0d30e073258214340120814404218a440437012290444346
 * 3f2bafdd4ae0000088feffff80665208f30100003a0400000020804609480a4947188c22
 * 9200b418aa46388800282fd0021c0649500040180188552a0ad8044d0ee0000000000002
 * 3c1f000012a2520889010000164bd0180004020cc5256d0048462080012060804346a380
 * 114bd018800050440068a060a1810020a073281c7ff060ff0d30e0732582143401218944
 * 0237012290444346132bc6dd4846306038bc9846a146aa46f0bc02bc08470000abff0000
 * 71020000
 */

/* The menu header of src/0803D320.c and src/08049E10.c with 20-byte rows.
 * The storage bound is the most rows a call can write: mode 1 emits at most
 * one per entry of the 64-entry table. */
typedef struct {
    u16 index;
    u16 enabled;
    u16 slot;
    u16 unknown_06;
    const u8 *name;
    u16 field_0C;
    u8 field_0E;
    u8 field_0F;
    u16 field_10;
    u8 unknown_12[2];
} ItemMenuRow;

typedef struct {
    s32 count;
    const void *table;
    u8 unknown_08[4];
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u16 field_10;
    u8 field_12;
    u8 unknown_13;
    u16 field_14;
    u8 field_16;
    u8 field_17;
    ItemMenuRow *rows;
    u8 unknown_1C[0x214];
    ItemMenuRow storage[64];
} ItemMenu;

/* Entries 1 to 127 of g_table_08521214 hold 375 + n in their first halfword
 * (entry 0 is all zero), so an item number indexes the table as [item - 375].
 * The compiler folds that base into the literal word 0x0851FAA4, which is
 * 375 entries below the table with g_table_08520080 lying in between;
 * src/08037A30.c makes the same pair of lookups and its ROM adds 0xFFFFE890
 * to the table address at run time. */
typedef struct {
    u16 index;
    u8 category;
    u8 unknown_03[13];
} ItemCategory;

/* The 64 four-byte entries at 0x02002B08 that src/08061E70.c and
 * src/0804D814.c scan; this function's literals are 0x02000000 plus the
 * offsets 0x2B08, 0x2B0A and 0x1F3C. */
typedef struct {
    u8 id;
    u8 unknown_01;
    u16 value;
} SlotEntry;

typedef struct {
    u8 unknown_00[0x1F3C];
    u16 items[20];
    u8 unknown_1F64[0xBA4];
    SlotEntry entries[64];
} EntryState;

extern EntryState g_state_02000000;
extern const u8 *const g_table_08526680[];
extern const ItemCategory g_table_08521214[];
extern const u16 data_0852A212[];
extern u8 func_080CB99C(u16 id);

s32 func_0804B95C(ItemMenu *menu, s32 mode)
{
    s32 count;
    s32 i;
    ItemMenuRow *row;
    ItemMenuRow *rows;

    menu->table = g_table_08526680;
    menu->x = 0;
    menu->y = 0;
    menu->width = 15;
    menu->height = 15;
    menu->field_10 = 0x1AD;
    menu->field_12 = 0;
    menu->field_14 = 0;
    menu->field_16 = 16;
    menu->field_17 = 0;
    rows = menu->storage;
    menu->rows = rows;
    count = 0;
    switch (mode) {
    case 1:
        for (i = 0; i < 64; i++) {
            if (g_state_02000000.entries[i].id != 0) {
                /* The ROM computes all of these before the first row
                 * store. */
                u16 item = g_table_08521214[g_state_02000000.entries[i].id].index;
                const ItemCategory *category = &g_table_08521214[item - 375];
                u16 graphic = category->category
                    ? 0x18A + category->category : 0;
                u16 id = item - 376;
                const u8 *name = g_table_08526680[id + 0x1F3];
                u16 enabled;

                if (g_state_02000000.entries[i].value != 0)
                    enabled = 0;
                else
                    enabled = 1;
                row = &rows[count];
                row->index = count;
                row->enabled = enabled;
                row->slot = i;
                row->name = name;
                row->field_0C = id + 0x43A;
                row->field_0E = 0;
                row->field_0F = func_080CB99C(graphic) + 13;
                row->field_10 = graphic;
                count++;
            }
        }
        break;
    case 2:
        for (i = 0; i < 20; i++) {
            if (g_state_02000000.items[i] != 0) {
                u16 id = g_state_02000000.items[i];
                /* The ROM reads this before the comparison rebases id. */
                u16 text = data_0852A212[id];
                u16 graphic;

                if (id <= 85) {
                    graphic = 0x189;
                } else {
                    id += (u16)-85;
                    graphic = 0x18A;
                }
                row = &rows[count];
                row->index = count;
                row->enabled = 1;
                row->slot = i;
                row->name = g_table_08526680[id + 0x271];
                row->field_0C = text;
                row->field_0E = 0;
                row->field_0F = func_080CB99C(graphic) + 13;
                row->field_10 = graphic;
                count++;
            }
        }
        break;
    }
    menu->count = count;
    return count;
}
