#include "ffta.h"

typedef struct ScriptContext {
    u8 bank;
    u8 index;
    s16 position;
    const u8 *script;
} ScriptContext;

extern u8 g_state_02000000[];
extern u32 func_0800A10C(ScriptContext *context);

/* 0x0800A0B8..0x0800A10C, 84 bytes including both literal pools. */
u32 func_0800A0B8(u32 mode, u32 enabled)
{
    ScriptContext context;
    u8 use_index = enabled;

    context.bank = mode;
    if (use_index)
        context.index = g_state_02000000[0x2191];
    else
        context.index = 0;
    return func_0800A10C(&context);
}
