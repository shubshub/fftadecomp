#include "ffta.h"

struct __attribute__((packed)) SelectedResource {
    u16 id : 10;
    u16 unknown_0A : 6;
};

struct ResourceSelection {
    const struct SelectedResource *current;
    u32 unknown_04;
    u32 unknown_08;
    u16 id;
};

struct __attribute__((packed)) ItemDefinition {
    u8 unknown_00[0x45];
    u8 category;
};

struct ScriptEntry {
    u8 name;
    u8 unknown_01[11];
};

extern struct ResourceSelection g_state_020020D0;
extern const struct ItemDefinition g_table_0855AE4C[];
extern const struct ScriptEntry g_table_08563A70[];
extern const u8 *const g_table_08526680[];
extern u16 func_08018C24(u8 *destination, const u8 *text);

/* 08019758..080197BC: 100 bytes, 38 instructions. */
u32 func_08019758(u8 *destination)
{
    u32 item_offset = (g_state_020020D0.current
        ? g_state_020020D0.current->id : g_state_020020D0.id)
        * sizeof(struct ItemDefinition);
    const struct ItemDefinition *item = (const struct ItemDefinition *)
        ((const u8 *)g_table_0855AE4C + item_offset);
    u32 script_offset = item->category * sizeof(struct ScriptEntry);
    const struct ScriptEntry *script = (const struct ScriptEntry *)
        ((const u8 *)g_table_08563A70 + script_offset);

    func_08018C24(destination, g_table_08526680[script->name + 0x2CD]);
    return 0;
}
