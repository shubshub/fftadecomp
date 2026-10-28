#include "ffta.h"

/* 0x0804B95C..0x0804BB10: 436 bytes. */
typedef struct {
    u16 index;
    u16 disabled;
    u16 source;
    u8 unknown_06[2];
    const u8 *text;
    u16 textId;
    u8 left;
    u8 right;
    u16 name;
    u8 unknown_12[2];
} MenuEntry;

typedef struct {
    u32 count;
    const u8 **textTable;
    u8 unknown_08[4];
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u16 tile;
    u8 style;
    u8 unknown_13;
    u16 selection;
    u8 visible;
    u8 scroll;
    MenuEntry *items;
    u8 unknown_1C[0x214];
    MenuEntry entries[1];
} Menu;

typedef struct {
    u16 kind;
    u8 unknown_02[14];
} ItemKind;

typedef struct {
    u8 unknown_00[2];
    u8 name;
    u8 unknown_03[13];
} KindInfo;

typedef struct {
    u8 code;
    u8 unknown_01;
    u16 available;
} InventoryEntry;

typedef struct {
    u8 unknown_00[0x1F3C];
    u16 specialItems[20];
    u8 unknown_1F64[0xBA4];
    InventoryEntry inventory[64];
} GameState;

extern const u8 *g_table_08526680[];
extern const ItemKind g_table_08521214[];
extern const KindInfo data_0851FAA4[];
extern const u16 data_0852A212[];
extern GameState g_state_02000000;
extern u32 func_080CB99C(u16);

u32 func_0804B95C(Menu *menu, s32 mode)
{
    u32 count;
    s32 i;

    menu->textTable = g_table_08526680;
    menu->x = 0;
    menu->y = 0;
    menu->width = 15;
    menu->height = 15;
    menu->tile = 0x1AD;
    menu->style = 0;
    menu->selection = 0;
    menu->visible = 16;
    menu->scroll = 0;
    menu->items = menu->entries;
    count = 0;
    switch (mode) {
    case 1:
        {
            GameState *state;
            u16 *available;
            MenuEntry *entry;

            i = 0;
            state = &g_state_02000000;
            available = &state->inventory[0].available;
            entry = menu->entries;
            for (; i < 64; available += 2, ++i) {
                if (g_state_02000000.inventory[i].code) {
                    u32 kind = g_table_08521214[g_state_02000000.inventory[i].code].kind;
                    u16 name;
                    u16 index;
                    const u8 *text;
                    u16 disabled;

                    if (data_0851FAA4[kind].name)
                        name = 0x18A + data_0851FAA4[kind].name;
                    else
                        name = 0;
                    index = kind - 0x178;
                    text = g_table_08526680[index + 0x1F3];
                    if (*available)
                        disabled = 0;
                    else
                        disabled = 1;
                    entry->index = count;
                    entry->disabled = disabled;
                    entry->source = i;
                    entry->text = text;
                    entry->textId = index + 0x43A;
                    entry->left = 0;
                    entry->right = func_080CB99C(name) + 13;
                    entry->name = name;
                    ++entry;
                    ++count;
                }
            }
        }
        break;
    case 2:
        {
            GameState *state;
            u16 *item;
            MenuEntry *entry;

            i = 0;
            state = &g_state_02000000;
            item = state->specialItems;
            entry = menu->entries;
            for (; i < 20; ++item, ++i) {
                if (*item) {
                    u16 index = *item;
                    u16 textId = data_0852A212[index];
                    u16 name;

                    if (index <= 0x55)
                        name = 0x189;
                    else {
                        index += (u16)-0x55;
                        name = 0x18A;
                    }
                    entry->index = count;
                    entry->disabled = 1;
                    entry->source = i;
                    entry->text = g_table_08526680[index + 0x271];
                    entry->textId = textId;
                    entry->left = 0;
                    entry->right = func_080CB99C(name) + 13;
                    entry->name = name;
                    ++entry;
                    ++count;
                }
            }
        }
        break;
    }
    menu->count = count;
    return count;
}
