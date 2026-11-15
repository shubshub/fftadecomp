#include "ffta.h"

/* Complete target: [0x080CF118, 0x080CF310), 504 bytes, 234 instructions,
 * seven literal words in two pools.
 * f0b557464e464546e0b483b080460906090e00910020814641460a7848780321084000021043
 * 4621414333480d180422424492460127019751460878002868d000234246177856782c4c0294
 * 227850460078824256d10320304000026188384381424fd10021002060806170009900294fd0
 * 281c3630007890421ad1281c41300078291c42310978090201431020014000290ed00f260f20
 * 4a461040002808d1174802680298042173f044f84f463743b946281c373000782478a04229d1
 * 281c41300078291c42310978090201432020014000291dd0f024f02049460840002817d10748
 * 02680298042173f023f84a46224391460de000004cae5508082b0002b8d43608043402980430
 * 029001333f2b9cdd01218a44019a013a0192002a8bda00204746787138712f48814600242f4f
 * 17210191e319424610785178032631400902da8a01438a4205d10020d882198d484608401885
 * 8420400024180199013901910029e6daa87807220240012a33d100251f4c2379617911400902
 * 47463a7878783040000219431043814210d0061c221d231c0127063206330135042d07dc1c1c
 * 11785078384000020843b042f2d1a17840200143a17000202071627902381040607120200140
 * 002905d009480268201c062172f0aeff03b038bc9846a146aa46f0bc01bc0047fbff00008000
 * 0002342e0002b8d43608
 */

typedef struct {
    u16 id : 10;
    u16 unknown_0A : 6;
    u8 unknown_flags_low : 2;
    u8 status : 3;
    u8 unknown_flags_high : 3;
    u8 unknown_03;
    u8 unknown_04[12];
} __attribute__((packed)) Item;

/* One 0x46-byte row.  Byte 2 is declared as src/080D29D4.c declares it and the
 * halfword at 0x41 as src/080D2D54.c declares it; this function also reads
 * the bytes at 0x36 and 0x37. */
typedef struct {
    u8 unknown_00[2];
    u8 unknown_02_low : 3;
    u8 kind : 3;
    u8 unknown_02_high : 2;
    u8 unknown_03[0x33];
    u8 unknown_36;
    u8 unknown_37;
    u8 unknown_38[9];
    u16 flags;
    u8 unknown_43[3];
} __attribute__((packed)) ItemMetadata;

/* Declared as src/080CEECC.c declares it.  This function compares `count`
 * with the item id and clears it. */
typedef struct {
    u8 value;
    u8 unknown_01;
    u16 count;
} SlotEntry;

typedef struct {
    u8 unknown_00[0x16];
    u16 item_id;
    u8 unknown_18[0x10];
    u16 flags;
    u8 unknown_2A[0xDE];
} Unit;

/* The 6-byte record as src/080D0F74.c declares it; the state holds five of
 * them at 0x2E34. */
typedef struct {
    u8 category : 3;
    u8 unknown_03 : 5;
    u8 unknown_08 : 7;
    u8 disabled : 1;
    u8 selection : 5;
    u8 primary : 1;
    u8 secondary : 1;
    u8 resource : 8;
    u8 unknown_1f : 1;
    u16 id : 9;
    u16 unknown_29 : 7;
} __attribute__((packed)) ActionEntry;

typedef struct {
    u8 unknown_00[0x2B08];
    SlotEntry entries[64];
    u8 unknown_2C08[0x22C];
    ActionEntry records[5];
} ItemListState;

extern ItemListState g_state_02000000;
extern const ItemMetadata g_table_0855AE4C[];
extern Unit g_state_02000080[24];
extern void (*g_callbacks_0836D4B8[])(void *, u32);

void func_080CF118(Item *item, u8 enabled)
{
    u8 cleared = 0;
    const ItemMetadata *metadata = &g_table_0855AE4C[item->id];
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        if (item->unknown_04[i] != 0) {
            for (j = 0; j < 64; j++) {
                SlotEntry *entry = &g_state_02000000.entries[j];

                if (entry->value == item->unknown_04[i] && entry->count == item->id) {
                    entry->count = 0;
                    entry->unknown_01 = 0;
                    if (enabled) {
                        if (metadata->unknown_36 == entry->value && (metadata->flags & 0x10) &&
                            !(cleared & 0x0F)) {
                            g_callbacks_0836D4B8[0](entry, sizeof(*entry));
                            cleared |= 0x0F;
                        }
                        if (metadata->unknown_37 == entry->value && (metadata->flags & 0x20) &&
                            !(cleared & 0xF0)) {
                            g_callbacks_0836D4B8[0](entry, sizeof(*entry));
                            cleared |= 0xF0;
                        }
                    }
                    break;
                }
            }
        }
    }
    item->unknown_04[1] = 0;
    item->unknown_04[0] = 0;

    for (i = 0; i < 24; i++) {
        Unit *unit = &g_state_02000080[i];

        if (unit->item_id == item->id) {
            unit->item_id = 0;
            unit->flags &= ~4;
        }
    }
    if (metadata->unknown_02_low == 1) {
        ActionEntry *record;
        s32 k;

        /* When no record carries the id the search ends on the last record,
         * which is then used; the ROM has no not-found path. */
        for (k = 0; k < 5; k++) {
            record = &g_state_02000000.records[k];
            if (record->id == item->id)
                break;
        }
        record->secondary = 1;
        record->id = 0;
        if (record->primary)
            g_callbacks_0836D4B8[0](record, sizeof(*record));
    }
}
