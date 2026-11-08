#include "ffta.h"

/* Target: complete [0x0805064C, 0x08050734), 232 bytes. */
typedef struct __attribute__((packed)) {
    u16 identifier : 10;
    u16 unknown_0A : 6;
} Unit;

typedef union {
    const Unit *unit;
    const u8 *record;
    u32 value;
    const char *text;
} MenuEntry;

typedef struct {
    u8 unknown_000[0x424];
    MenuEntry entries[64];
    u32 identifiers[64];
} MenuItems;

typedef struct {
    MenuItems *items;
    u8 unknown_04[4];
    u8 kind;
} MenuState;

extern const char *const g_table_085567F0[];
extern const char *const g_table_0855A64C[];
extern const char *const g_table_08526680[];
extern const char *func_080CB4E0(u32 identifier);

const char *func_0805064C(MenuState *menu, u16 index)
{
    const Unit *unit;
    const u8 *record;
    u16 offset;

    switch (menu->kind) {
    case 1:
        return g_table_085567F0[menu->items->identifiers[(s16)index]];
    case 3:
        unit = menu->items->entries[(s16)index].unit;
        return g_table_0855A64C[unit->identifier];
    case 4:
        record = menu->items->entries[(s16)index].record;
        offset = 0x1F2 + *record;
        return g_table_08526680[offset];
    case 5:
        return func_080CB4E0((u16)menu->items->entries[(s16)index].value);
    case 6:
        return menu->items->entries[(s16)index].text;
    }
    return g_table_085567F0[0];
}
