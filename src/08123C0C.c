#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x3C2A];
    u8 selected;
} ScriptSelectionState;

typedef struct {
    u8 unknown_00[8];
    u16 flags;
    u16 unknown_0A;
} ScriptSelectionEntry;

extern ScriptSelectionState g_state_02000000;
extern const ScriptSelectionEntry g_table_08563A70[];

u32 func_08123C0C(u16 *context, const u8 *script)
{
    u32 entryOffset = g_state_02000000.selected * sizeof(ScriptSelectionEntry);
    const ScriptSelectionEntry *entry =
        (const ScriptSelectionEntry *)((const u8 *)g_table_08563A70 + entryOffset);

    if (!(entry->flags & 2))
        *context += script[1] | (script[2] << 8);
    return 0x110;
}
