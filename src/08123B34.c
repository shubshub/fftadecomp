#include "ffta.h"

typedef struct {
    u16 offset;
} ScriptContext;

typedef struct {
    u8 unknown_0000[0x21B4];
    u8 value;
} ScriptBranchState;

extern ScriptBranchState g_state_02000000;

u32 func_08123B34(ScriptContext *context, const u8 *script)
{
    if (g_state_02000000.value > script[1]) {
        u32 displacement = script[2] | (script[3] << 8);

        context->offset += displacement;
    }
    return 0x110;
}
