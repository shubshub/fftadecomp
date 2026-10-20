#include "script_entry.h"

typedef struct {
    u16 offset;
} ScriptContext;

typedef struct {
    u8 unknown_0000[0x3C2A];
    u8 index;
} ScriptBranchState;

extern ScriptBranchState g_state_02000000;

u32 func_08123BC8(ScriptContext *context, const u8 *script)
{
    u32 record_offset = g_state_02000000.index * sizeof(ScriptEntry);
    const ScriptEntry *record = (const ScriptEntry *)
        ((const u8 *)g_table_08563A70 + record_offset);

    if (record->flags & 1) {
        u32 displacement = script[1] | (script[2] << 8);

        context->offset += displacement;
    }
    return 0x110;
}
