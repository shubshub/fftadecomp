#include "ffta.h"

typedef struct {
    u16 offset;
} ScriptContext;

typedef struct {
    u8 unknown_0000[0x3C2A];
    u8 index;
} ScriptBranchState;

typedef struct {
    u8 unknown_00[8];
    u16 flags;
    u8 unknown_0A[2];
} BranchRecord;

extern ScriptBranchState g_state_02000000;
extern const BranchRecord g_table_08563A70[];

u32 func_08123BC8(ScriptContext *context, const u8 *script)
{
    u32 record_offset = g_state_02000000.index * sizeof(BranchRecord);
    const BranchRecord *record = (const BranchRecord *)
        ((const u8 *)g_table_08563A70 + record_offset);

    if (record->flags & 1) {
        u32 displacement = script[1] | (script[2] << 8);

        context->offset += displacement;
    }
    return 0x110;
}
