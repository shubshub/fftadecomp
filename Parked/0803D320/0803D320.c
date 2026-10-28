#include "ffta.h"

typedef struct {
    u8 unknown_00[3];
    u8 value;
    u8 unknown_04[8];
} SourceRecord;

typedef struct {
    u8 unknown_00[0xB0];
    SourceRecord records[31];
} SourceData;

typedef struct {
    SourceData *source;
} MenuContext;

typedef struct {
    u16 index;
    u16 state;
    u8 unknown_04[4];
    const u8 *text;
    u16 id;
    u8 value;
    u8 source_index;
    u8 unknown_10[4];
} MenuEntry;

typedef struct {
    s32 count;
    const void *title;
    u8 unknown_08[4];
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u16 tile;
    u8 mode;
    u8 unknown_13;
    u16 selection;
    u8 spacing;
    u8 flags;
    MenuEntry *entries;
    u8 unknown_1C[0x230 - 0x1C];
    MenuEntry storage[31];
} Menu;

extern MenuContext *g_state_03002810;
extern const u8 *const g_table_085567F0[];
extern const u8 *const g_table_08526680[];
extern const u16 data_0839191C[];

/* 0803D320..0803D3DC: 188 bytes, 83 reachable instructions. */
s32 func_0803D320(Menu *menu)
{
    s32 count;
    s32 index;
    MenuContext *context;
    MenuEntry *entry;

    menu->title = g_table_085567F0;
    menu->x = 0;
    menu->y = 0;
    menu->width = 14;
    menu->height = 15;
    menu->tile = 0xCB;
    menu->mode = 0;
    menu->selection = 0;
    menu->spacing = 16;
    menu->flags = 0;
    menu->entries = menu->storage;
    count = 0;
    index = 0;
    context = g_state_03002810;
    entry = menu->entries;
    for (; index <= 30; index++) {
        if (context->source->records[index].value) {
            const u8 *text = g_table_08526680[index + 0x2CE];
            entry->index = count;
            entry->state = 0;
            entry->text = text;
            entry->id = data_0839191C[index + 1];
            entry->value = context->source->records[index].value;
            entry->source_index = index;
            entry++;
            count++;
        }
    }
    menu->count = count;
    return count;
}
