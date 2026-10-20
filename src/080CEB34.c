#include "script_entry.h"

typedef struct {
    u8 unknown_0000[0x3C28];
    u16 override_index;
    u8 selected;
} SelectionState;

extern u8 g_state_02000000[];
extern const u32 g_table_0855A64C[];
extern const u8 g_table_08564670[][27];
extern const u32 g_table_08565F14[];

u32 func_080CEB34(u8 mode)
{
    const ScriptEntry *entry;
    const u8 *record;

    if (mode == 0) {
        if (((const SelectionState *)g_state_02000000)->override_index != 0)
            return g_table_0855A64C[((const SelectionState *)g_state_02000000)->override_index];
        entry = &g_table_08563A70[((const SelectionState *)g_state_02000000)->selected];
        record = g_table_08564670[entry->selector];
        return g_table_08565F14[record[0]];
    } else if (mode == 1) {
        return g_table_0855A64C[((const SelectionState *)g_state_02000000)->override_index];
    } else {
        entry = &g_table_08563A70[((const SelectionState *)g_state_02000000)->selected];
        record = g_table_08564670[entry->selector];
        return g_table_08565F14[record[0]];
    }
}
