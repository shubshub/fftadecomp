#include "ffta.h"

/* Complete target: [0x0812C030, 0x0812C170), 320 bytes, 146 instructions,
 * six literal words in two pools.
 * f0b557464e464546e0b482b080460d1c2a786878032108400002104346214143134809180091
 * 0024281d82460021894656463019007829788c466f7800281ed0002301900320384002020a43
 * 9800094e8019464631180878019eb0420cd14888904209d1002048804846487007e000004cae
 * 5508082b000001333f2be6dd0134012cd5dd00206871287103203840030261460b4342469632
 * 00262548814684256d0017241088984204d11680518a4846084050825219013c002cf3da009e
 * b1780720084001282bd10025032007403c02604604430126174a424417484044031c11785078
 * 304000020843a04204d00632981d0135042df2dd9978402001439970002018715a7902381040
 * 587120200140002905d009480268181c062116f07ef802b038bc9846a146aa46f0bc01bc0047
 * fbff0000382e0000342e0000b8d43608
 *
 * The same removal as src/080CF118.c, made on a state passed by pointer
 * rather than on g_state_02000000, and without that function's `enabled`
 * callbacks inside the slot search.
 */

/* Declared as src/080CF118.c declares it. */
typedef struct {
    u16 id : 10;
    u16 unknown_0A : 6;
    u8 unknown_flags_low : 2;
    u8 status : 3;
    u8 unknown_flags_high : 3;
    u8 unknown_03;
    u8 unknown_04[12];
} __attribute__((packed)) Item;

/* One 0x46-byte row, as src/080CF060.c declares it. */
typedef struct {
    u8 unknown_00[2];
    u8 unknown_02_low : 3;
    u8 kind : 3;
    u8 unknown_02_high : 2;
    u8 unknown_03[0x43];
} __attribute__((packed)) ItemMetadata;

/* Declared as src/080CEECC.c declares it. */
typedef struct {
    u8 value;
    u8 unknown_01;
    u16 count;
} SlotEntry;

/* The 0x108-byte unit of src/080CF118.c, whose array starts at 0x02000080. */
typedef struct {
    u8 unknown_00[0x16];
    u16 item_id;
    u8 unknown_18[0x10];
    u16 flags;
    u8 unknown_2A[0xDE];
} Unit;

/* The 6-byte record as src/080D0F74.c declares it. */
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

/* The layout src/080CF118.c reads at 0x02000000: units at 0x80 (0x96 and
 * 0xA8 here are units[0].item_id and units[0].flags), the slot entries at
 * 0x2B08 and the five records at 0x2E34. */
typedef struct {
    u8 unknown_0000[0x80];
    Unit units[24];
    u8 unknown_1940[0x2B08 - 0x1940];
    SlotEntry entries[64];
    u8 unknown_2C08[0x22C];
    ActionEntry records[5];
} ItemListState;

extern const ItemMetadata g_table_0855AE4C[];
extern void (*g_callbacks_0836D4B8[])(void *, u32);

void func_0812C030(ItemListState *state, Item *item)
{
    const ItemMetadata *metadata = &g_table_0855AE4C[item->id];
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        if (item->unknown_04[i] != 0) {
            for (j = 0; j < 64; j++) {
                SlotEntry *entry = &state->entries[j];

                if (entry->value == item->unknown_04[i] && entry->count == item->id) {
                    entry->count = 0;
                    entry->unknown_01 = 0;
                    break;
                }
            }
        }
    }
    item->unknown_04[1] = 0;
    item->unknown_04[0] = 0;

    for (i = 0; i < 24; i++) {
        Unit *unit = &state->units[i];

        if (unit->item_id == item->id) {
            unit->item_id = 0;
            unit->flags &= ~4;
        }
    }
    if (metadata->unknown_02_low == 1) {
        ActionEntry *record;
        s32 k;

        /* When no record carries the id the search (0x0812C10E-0x0812C126)
         * ends on the last record, which is then used at 0x0812C128; the ROM
         * has no not-found path. */
        for (k = 0; k < 5; k++) {
            record = &state->records[k];
            if (record->id == item->id)
                break;
        }
        record->secondary = 1;
        record->id = 0;
        if (record->primary)
            g_callbacks_0836D4B8[0](record, sizeof(*record));
    }
}
