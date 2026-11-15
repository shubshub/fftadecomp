#include "ffta.h"

typedef struct {
    u16 id : 10;
    u16 unknown_0A : 6;
    u8 unknown_02;
    u8 quantity;
} __attribute__((packed)) SlotItem;

typedef struct {
    u8 unknown_00[0x1D];
    u8 group;
    u8 unknown_1E[6];
    SlotItem *items[16];
} ItemPanel;

typedef struct {
    u8 unknown_00;
    u8 flags;
    u8 unknown_02[10];
} GroupState;

typedef struct {
    u8 unknown_00[0xB0];
    GroupState groups[30];
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
    u16 order;
    u16 unknown_06;
    const void *label;
    u16 value;
    u8 kind;
    u8 quantity;
    u16 id;
    u8 ordinal;
    u8 unknown_13;
} MenuEntry;

typedef struct {
    u8 unknown_00[4];
    u16 value;
    u8 unknown_06[2];
} ValueRecord;

extern MenuState *g_state_03002810;
extern const ItemDefinition g_table_0855AE4C[];
extern const void *const g_table_0855A64C[];
extern const ValueRecord data_08391B58[];
extern const void *const data_085668B0[];

/* Complete target: [0x0803CEF8, 0x0803D034), 316 bytes, 147 instructions. */
s32 func_0803CEF8(s32 *count, s32 group, MenuEntry *entries, u8 category)
{
    s32 total = 0;
    s32 index = *count;
    u8 ordinal;
    s32 slot;
    s32 id;

    group--;
    ordinal = 0;
    for (slot = 0; slot <= 15; slot++) {
        SlotItem *item = g_state_03002810->panel->items[slot];
        const ItemDefinition *definition = &g_table_0855AE4C[item->id];
        if (item != 0 && item->id != 0) {
            entries[index].index = index;
            entries[index].category = category;
            entries[index].order = g_state_03002810->panel->group;
            entries[index].label = g_table_0855A64C[item->id];
            entries[index].value = data_08391B58[0].value;
            entries[index].kind = definition->width + 8;
            entries[index].quantity = item->quantity;
            entries[index].id = item->id;
            entries[index].ordinal = ordinal++;
            index++;
            total++;
        }
    }

    if ((g_state_03002810->groups->groups[group].flags & 5) == 5) {
        /* The entry func_0803CDAC builds five of, continuing its
         * data_085668B0 sequence.  Each of those blocks sets id first and
         * uses it for the value record and the id member; here it is fixed. */
        id = 0;
        entries[index].index = index;
        entries[index].category = 1;
        entries[index].order = index;
        entries[index].label = data_085668B0[7];
        entries[index].value = data_08391B58[id].value;
        entries[index].kind = 12;
        entries[index].quantity = 0xFF;
        entries[index].id = id;
        index++;
    }
    *count = index;
    return total;
}
