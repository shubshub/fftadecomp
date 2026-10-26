#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u8 job;
    u8 unknown_07[0x34];
    u8 selected;
} Unit;

typedef struct {
    u8 unknown_00[4];
    u8 value;
    u8 unknown_05[3];
} SelectionInfo;

extern const SelectionInfo *const g_table_0851BA84[];

u8 func_080CD50C(Unit *unit)
{
    u32 selected;
    u8 value;

    if (unit)
        selected = unit->selected;
    else
        selected = 0;

    if (selected) {
        u32 job = unit->job;
        u32 selection = unit->selected;
        const SelectionInfo *info = g_table_0851BA84[job];
        value = info[selection].value;
    } else {
        value = 0;
    }
    return value;
}
