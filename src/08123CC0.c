#include "script_record.h"

typedef struct {
    u16 offset;
} ScriptContext;

u16 func_0800A024(void);

u32 func_08123CC0(ScriptContext *context, const u8 *script)
{
    u16 index = func_0800A024();
    const ScriptRecord *record = &g_table_0854CD54[index];

    if (!record->value22) {
        u32 displacement = script[1] | (script[2] << 8);

        context->offset += displacement;
    }
    return 0x110;
}
