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
extern u32 func_080CCD50(u16 index, u8 selector);
extern u8 func_080CDB3C(const Unit *unit);
extern u16 func_080258C4(const void *unit, u16 value);
extern u16 func_080161BC(const u8 *text);

/* Raise the list severity for an entry that has a cost: at least 3, and 4
 * when the cost is over 99.  The ROM has this block twice here, register
 * for register: 0x0802715A-0x0802716A and 0x0802718E-0x0802719E.  It is
 * also twice in func_08026D44 (0x08026DFA-0x08026E0A, 0x08026E36-0x08026E46;
 * this macro text reproduces src/08026D44.c) and twice in func_08026F9C
 * (0x0802702E-0x0802703E, 0x08027054-0x08027064). */
#define RAISE_SEVERITY(list, cost)                                     \
    do {                                                               \
        if ((list)->severity < 3)                                      \
            (list)->severity = 3;                                      \
        if ((cost) > 99)                                               \
            (list)->severity = 4;                                      \
    } while (0)

/* Complete target: [0x080270CC, 0x08027208), 316 bytes, 142 instructions.
 * f0b557464e464546e0b481b081460c1c803000900020207221798846824662799045
 * 76dc4046c10020684518a879012801d0042868d1a8881e21a5f023fe002862d0a988
 * c800401a80001649461848469430016852469000401841460160124f38688069a6f0
 * 04fd000600281ed0a8881421a5f007fe002818d1307900282ed0386880693179fef7
 * b7fb0006010e207a022801d803202072632920d9042020721de000007c18550838f4
 * 0002307900281bd0204d286880693179fef79dfb0006010e207a022801d803202072
 * 632901d90420207228688069808b884205d248469830006850440021017001229244
 * 12493088800040180068eef7faff0006000ee179884200d9e0710122904460798045
 * 88dd207a002802d00920009948735246627201b038bc9846a146aa46f0bc01bc0047
 * 000038f40002f0675508
 */
void func_080270CC(MenuContext *context, MenuList *list)
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
            func_080CCD50(entry->id, 0x1E)) {
            const ResourceEntry *resource = &data_0855187C[entry->id];
            u8 width;

            context->indices[count] = i;
            if (func_080CDB3C(data_0200F438->unit) &&
                !func_080CCD50(entry->id, 0x14)) {
                if (resource->cost) {
                    u32 cost = (u8)func_080258C4(data_0200F438->unit, resource->cost);

                    RAISE_SEVERITY(list, cost);
                }
                context->enabled[count] = 0;
            } else if (resource->cost) {
                u32 cost = (u8)func_080258C4(data_0200F438->unit, resource->cost);

                RAISE_SEVERITY(list, cost);
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
