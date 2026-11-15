#include "ffta.h"

/* Complete target: [0x080CF060, 0x080CF118), 184 bytes, 84 instructions, four
 * literal words.
 * f0b557464e464546e0b481b084460020009061460a78487803210840030213434620584320494018
 * 807807220240012a31d1002080461d4e317970791040000208431b4989198a4698421ad0351d371c
 * 012081460635063701218844404604280fdc3e1c2c786a7849460a401202604603784078032108400002
 * 224318438242e8d1b078c0060b495144c00e0978884201d101210091009801b038bc9846a146aa46
 * f0bc02bc08474cae5508342e0002ccd1ffff691f0000
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

/* One 0x46-byte row.  Byte 2 is declared as src/080D29D4.c declares it; this
 * function tests its low three bits. */
typedef struct {
    u8 unknown_00[2];
    u8 unknown_02_low : 3;
    u8 kind : 3;
    u8 unknown_02_high : 2;
    u8 unknown_03[0x43];
} __attribute__((packed)) ItemMetadata;

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
    u8 unknown_00[0x1F69];
    u8 selected;
    u8 unknown_1F6A[0xECA];
    ActionEntry records[5];
} ItemListState;

extern ItemListState g_state_02000000;
extern const ItemMetadata g_table_0855AE4C[];

u32 func_080CF060(Item *item)
{
    u32 result = 0;
    const ItemMetadata *metadata = &g_table_0855AE4C[item->id];

    if (metadata->unknown_02_low == 1) {
        ActionEntry *record;
        s32 i;

        /* When no record carries the id the search ends on the last record,
         * which is then used; the ROM has no not-found path. */
        for (i = 0; i < 5; i++) {
            record = &g_state_02000000.records[i];
            if (record->id == item->id)
                break;
        }
        if (record->selection == g_state_02000000.selected)
            result = 1;
    }
    return result;
}
