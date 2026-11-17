#include "ffta.h"

typedef struct {
    u8 unknown_00[0xc];
    u8 visible_entries;
    u8 state;
    u8 unknown_0e[6];
} MenuState;

typedef struct {
    u8 unknown_00[0x80];
    MenuState menu;
    s32 *indices;
    u8 *enabled;
} MenuContext;

typedef struct {
    u8 unknown_00[4];
    u16 id;
    u8 type;
    u8 unknown_07;
} MenuEntry;

typedef struct {
    MenuEntry *entries;
    u8 first;
    u8 last;
    u8 kind;
    u8 width;
    u8 severity;
    u8 count;
} MenuList;

typedef struct {
    u16 name;
    u8 unknown_02[2];
    u8 cost;
    u8 category;
    u8 unknown_06[22];
} ResourceEntry;

typedef struct {
    u8 unknown_00[0x1C];
    u16 points;
} Unit;

typedef struct {
    u8 unknown_00[0x18];
    Unit *unit;
} BattleContext;

extern BattleContext *data_0200F438;
extern const ResourceEntry data_0855187C[];
extern const void *g_table_085567F0[];
extern u8 func_080CD560(const void *object, u8 index);
extern u32 func_080CCD50(u16 index, u8 selector);
extern u8 func_080CDB3C(const Unit *unit);
extern u16 func_080161BC(const u8 *text);

/* Complete target: [0x08026F9C, 0x080270CC), 304 bytes, 138 instructions. */
void func_08026F9C(MenuContext *context, MenuList *list)
{
    MenuState *menu = &context->menu;
    s32 i;
    s32 count;

    list->severity = 0;
    i = list->first;
    count = 0;
    for (; i <= list->last; i++) {
        MenuEntry *entry = &list->entries[i];

        if ((entry->type == 1 || entry->type == 4) &&
            func_080CD560(data_0200F438->unit, i) &&
            func_080CCD50(entry->id, 0x15)) {
            const ResourceEntry *resource = &data_0855187C[entry->id];
            u8 width;

            context->indices[count] = i;
            if (func_080CDB3C(data_0200F438->unit) &&
                !func_080CCD50(entry->id, 0x14)) {
                if (resource->cost) {
                    u32 cost = resource->cost;

                    if (list->severity < 3)
                        list->severity = 3;
                    if (cost > 99)
                        list->severity = 4;
                }
                context->enabled[count] = 0;
            } else if (resource->cost) {
                u32 cost = resource->cost;

                if (list->severity < 3)
                    list->severity = 3;
                if (cost > 99)
                    list->severity = 4;
                if (data_0200F438->unit->points < cost)
                    context->enabled[count] = 0;
            }
            count++;
            width = func_080161BC(g_table_085567F0[resource->name]);
            if (width > list->width)
                list->width = width;
        }
    }
    if (list->severity)
        menu->state = 9;
    list->count = count;
}
