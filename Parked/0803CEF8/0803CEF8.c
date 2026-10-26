#include "ffta.h"

typedef struct {
    u16 id : 10;
    u16 unknown_0A : 6;
    u8 unknown_02;
    u8 quantity;
} __attribute__((packed)) SlotItem;

typedef struct {
    u8 unknown_00[0x1D];
    u8 page;
    u8 unknown_1E[6];
    SlotItem *items[16];
} ItemPanel;

typedef struct {
    u8 flags;
    u8 unknown_01[11];
} __attribute__((packed)) GroupState;

typedef struct {
    u8 unknown_00[0xB1];
    GroupState groups[0];
} GroupCollection;

typedef struct {
    GroupCollection *groups;
    ItemPanel *panel;
} MenuState;

typedef struct {
    u8 unknown_00[2];
    u8 unknown_10 : 3;
    u8 width : 3;
    u8 unknown_16 : 2;
    u8 unknown_03[0x43];
} __attribute__((packed)) ItemDefinition;

typedef struct {
    u16 index;
    u16 category;
    u16 page;
    u16 unknown_06;
    const void *label;
    u16 style;
    u8 width;
    u8 quantity;
    u16 id;
    u8 ordinal;
    u8 unknown_13;
} MenuEntry;

extern MenuState *g_state_03002810;
extern const ItemDefinition g_table_0855AE4C[];
extern const void *g_table_0855A64C[];
extern const u16 data_08391B58[];
extern const void *data_085668B0[];

/* Complete target: [0x0803CEF8, 0x0803D034), 316 bytes. */
s32 func_0803CEF8(s32 *next_index, s32 group, MenuEntry *entries, u8 category)
{
    s32 total = 0;
    s32 index = *next_index;
    u8 ordinal;
    s32 slot;

    group--;
    ordinal = 0;
    for (slot = 0; slot <= 15; slot++) {
        MenuState *state = g_state_03002810;
        SlotItem *item = state->panel->items[slot];
        const ItemDefinition *definition = &g_table_0855AE4C[item->id];
        if (item != 0 && item->id != 0) {
            entries[index].index = index;
            entries[index].category = category;
            entries[index].page = state->panel->page;
            entries[index].label = g_table_0855A64C[item->id];
            entries[index].style = data_08391B58[2];
            entries[index].width = definition->width + 8;
            entries[index].quantity = item->quantity;
            entries[index].id = item->id;
            entries[index].ordinal = ordinal++;
            index++;
            total++;
        }
    }

    if ((g_state_03002810->groups->groups[group].flags & 5) == 5) {
        entries[index].index = index;
        entries[index].category = 1;
        entries[index].page = index;
        entries[index].label = data_085668B0[7];
        entries[index].style = data_08391B58[2];
        entries[index].width = 12;
        entries[index].quantity = 0xFF;
        entries[index++].id = 0;
    }
    *next_index = index;
    return total;
}
