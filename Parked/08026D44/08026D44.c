#include "ffta.h"

/* 0x08026D44..0x08026F9C: 600 bytes. */
typedef struct {
    u8 unknown_00[0xD];
    u8 state;
    u8 unknown_0E[6];
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

typedef struct {
    u8 unknown_00[0x1F64];
    u32 currency;
} GameState;

extern BattleContext *data_0200F438;
extern GameState g_state_02000000;
extern const ResourceEntry data_0855187C[];
extern const void *g_table_085567F0[];
extern u32 func_080CD560(Unit *unit, u32 index);
extern u32 func_080C95A8(u32 value);
extern u32 func_080CCD50(u32 id, u32 category);
extern u32 func_080CDB3C(Unit *unit);
extern u32 func_080258C4(Unit *unit, u32 cost);
extern u32 func_080CD95C(Unit *unit);
extern u32 func_08026A7C(void);
extern u32 func_080267EC(Unit *unit, u32 category);
extern u32 func_08026838(Unit *unit);
extern u32 func_080268DC(u32 id);
extern u32 func_08026AB8(MenuContext *context);
extern u32 func_080161BC(const void *text);

void func_08026D44(MenuContext *context, MenuList *list)
{
    MenuState *menu = &context->menu;
    s32 i;
    s32 count;

    list->severity = 0;
    for (i = list->first, count = 0; i <= list->last; i++) {
        MenuEntry *entry = &list->entries[i];

        if ((entry->type == 1 || entry->type == 4) &&
            (u8)func_080CD560(data_0200F438->unit, (u8)i)) {
            u32 offset = entry->id * sizeof(ResourceEntry);
            const ResourceEntry *resource = (const ResourceEntry *)((const u8 *)data_0855187C + offset);
            u8 width;
            u32 allowed;

            context->indices[count] = i;
            allowed = (u8)func_080C95A8(0xD) != 1;
            if (!allowed)
                allowed = func_080CCD50(entry->id, 0x1F);
            if (!allowed) {
                context->enabled[count] = 0;
            } else if ((u8)func_080CDB3C(data_0200F438->unit) && func_080CCD50(entry->id, 0x14) == 0) {
                if (resource->cost) {
                    u32 cost = (u8)func_080258C4(data_0200F438->unit, resource->cost);

                    if (list->severity <= 2)
                        list->severity = 3;
                    if (cost > 99)
                        list->severity = 4;
                }
                context->enabled[count] = 0;
            } else if (resource->cost) {
                u32 cost = (u8)func_080258C4(data_0200F438->unit, resource->cost);

                if (list->severity <= 2)
                    list->severity = 3;
                if (cost > 99)
                    list->severity = 4;
                if (data_0200F438->unit->points < cost)
                    context->enabled[count] = 0;
            } else if ((u8)func_080CD95C(data_0200F438->unit) && list->kind == 0x15 && i != 0x1A) {
                context->enabled[count] = 0;
            } else if (entry->id == 0xD9 && g_state_02000000.currency <= 99) {
                context->enabled[count] = 0;
            } else if ((entry->id == 0x94 || entry->id == 0xD3) && (u8)func_08026A7C() == 0) {
                context->enabled[count] = 0;
            } else if ((entry->id == 0xDE || entry->id == 0x7C) && (u8)func_080267EC(data_0200F438->unit, resource->category) == 0) {
                context->enabled[count] = 0;
            } else if (entry->id == 0x58) {
                if ((u8)func_08026838(data_0200F438->unit))
                    context->enabled[count] = 0;
            } else if (entry->id >= 0xCA && entry->id <= 0xD2 && (u8)func_080268DC(entry->id) == 0) {
                context->enabled[count] = 0;
            } else if (entry->id == 0x21 && (u8)func_08026AB8(context) == 0) {
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
