#include "ffta.h"

typedef void (*BufferInitializer)(void *destination, u32 size);

typedef struct {
    u8 unknown_00[4];
    u16 count;
    u8 unknown_06[6];
    u8 visible_entries;
    u8 state;
    u8 unknown_0e[6];
} MenuState;

typedef struct {
    u8 unknown_00[0xA];
    u8 selection;
    u8 unknown_0B[0x75];
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
    u8 unknown_05[23];
} ResourceEntry;

typedef struct {
    u8 unknown_00[0x1C];
    u16 points;
    u8 unknown_1E[0x17];
    u8 override_1;
    u8 override_2;
    u8 override_3;
} Unit;

typedef struct {
    u8 unknown_00[0x18];
    Unit *unit;
} BattleContext;

typedef struct {
    u8 unknown_00[0x94];
    u16 flags;
} InputState;

typedef struct {
    u8 unknown_00[0xAC];
    u16 selection;
} SelectionState;

extern BattleContext *data_0200F438;
extern InputState g_state_0200F390;
extern SelectionState g_state_020020D0;
extern const ResourceEntry data_0855187C[];
extern BufferInitializer const g_callbacks_0836D4B8[];
extern s32 func_080C7EA4(const void *object, u32 selector);
extern u16 func_080258C4(const void *unit, u16 value);
extern const u8 *func_080CCE60(Unit *unit, u8 mode, u8 *first, u8 *second);
extern u8 func_080CD560(const void *object, u8 index);
extern u32 func_080CCD50(u16 index, u8 selector);
extern u8 func_080CDB3C(const Unit *unit);

// Complete target: [0x08027918, 0x08027AE6), 462 bytes, 231 instructions.
// Builds the cost list of all three categories in one local MenuList: the
// category walk of func_08026AB8 around the entry checks of func_080270CC.
void func_08027918(MenuContext *context)
{
    MenuState *menu = &context->menu;
    MenuList list;
    s32 reserved;
    s32 count;
    s32 category;

    g_callbacks_0836D4B8[0](&list, sizeof(list));
    context->selection = func_080C7EA4(data_0200F438->unit, 3);
    reserved = 0;
    if ((g_state_0200F390.flags & 0x60) == 0x60) {
        const ResourceEntry *selected = &data_0855187C[g_state_020020D0.selection];

        reserved = (u8)func_080258C4(data_0200F438->unit, selected->cost);
    }
    count = 0;
    for (category = 0; category < 3; category++) {
        s32 i;

        switch (category) {
        case 0:
            list.kind = data_0200F438->unit->override_1;
            break;
        case 1:
            list.kind = data_0200F438->unit->override_2;
            break;
        case 2:
            list.kind = data_0200F438->unit->override_3;
            break;
        }
        if (list.kind == 0)
            continue;
        list.entries = (MenuEntry *)func_080CCE60(data_0200F438->unit, category + 1,
                                                  &list.first, &list.last);
        for (i = list.first; i <= list.last; i++) {
            MenuEntry *entry = &list.entries[i];

            if ((entry->type == 1 || entry->type == 4) &&
                func_080CD560(data_0200F438->unit, i) &&
                func_080CCD50(entry->id, 0x13)) {
                const ResourceEntry *resource = &data_0855187C[entry->id];

                context->indices[count] = i;
                // A once-through block, as in func_08026D44.  Here the ROM keeps
                // the func_080CCD50(id, 0x14) half of its first check after
                // the cost check (0x08027A98, branching back to 0x08027A5C),
                // where agbcc puts a leading exit test when it closes a loop
                // statement.
                while (1) {
                    if (func_080CDB3C(data_0200F438->unit) &&
                        !func_080CCD50(entry->id, 0x14)) {
                        context->enabled[count] = 0;
                        break;
                    }
                    if (resource->cost) {
                        s32 cost = (u8)func_080258C4(data_0200F438->unit, resource->cost);

                        if (data_0200F438->unit->points - reserved < cost)
                            context->enabled[count] = 0;
                    }
                    break;
                }
                count++;
            }
        }
    }
    menu->state = 9;
    list.count = count;
    menu->count = list.count;
}
