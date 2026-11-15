#include "ffta.h"

/* Complete target: [0x0803D320, 0x0803D3DC), 188 bytes.
 * Builds the menu rows for the nonzero entries of the state's map.  The
 * map layout (12-byte entries from 0xB0, byte at +3) is the one
 * src/0803AD08.c reads; the menu header is the one src/08049E10.c fills.
 */
typedef struct {
    u8 unknown_00[3];
    u8 record;
    u8 unknown_04[8];
} MapEntry;

typedef struct {
    u8 unknown_000[0xB0];
    MapEntry entries[31];
} EntryMap;

typedef struct {
    const EntryMap *map;
} MenuContext;

typedef struct {
    u16 index;
    u16 field_02;
    u8 unknown_04[4];
    const u8 *text;
    u16 field_0C;
    u8 record;
    u8 entry;
    u8 unknown_10[4];
} MapMenuRow;

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
    MapMenuRow *rows;
    u8 unknown_1C[0x214];
    MapMenuRow storage[31];
} MapMenu;

extern MenuContext *g_state_03002810;
extern const u8 *const g_table_085567F0[];
extern const u8 *const g_table_08526680[];
extern const u16 data_0839191C[];

s32 func_0803D320(MapMenu *menu)
{
    s32 count;
    s32 i;
    MapMenuRow *row;
    MapMenuRow *rows;

    menu->table = g_table_085567F0;
    menu->x = 0;
    menu->y = 0;
    menu->width = 14;
    menu->height = 15;
    menu->field_10 = 203;
    menu->field_12 = 0;
    menu->field_14 = 0;
    menu->field_16 = 16;
    menu->field_17 = 0;
    rows = menu->storage;
    menu->rows = rows;
    count = 0;
    for (i = 0; i < 31; i++) {
        if (g_state_03002810->map->entries[i].record != 0) {
            /* The ROM loads the text pointer before the first row store. */
            const u8 *text = g_table_08526680[i + 0x2CE];

            row = &rows[count];
            row->index = count;
            row->field_02 = 0;
            row->text = text;
            row->field_0C = data_0839191C[i + 1];
            row->record = g_state_03002810->map->entries[i].record;
            row->entry = i;
            count++;
        }
    }
    menu->count = count;
    return count;
}
