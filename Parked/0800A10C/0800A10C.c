#include "ffta.h"

typedef struct ScriptContext {
    u8 bank;
    u8 index;
    s16 position;
    const u8 *script;
} ScriptContext;

extern const u8 g_table_08A1A908[];
extern u8 g_state_02000000[];

u32 func_0800A154(ScriptContext *context);

u8 func_0800A10C(ScriptContext *context)
{
    u8 result = 0;
    const u8 *bank = g_table_08A1A908 +
        ((const u16 *)g_table_08A1A908)[context->bank];

    context->script = bank + ((const u16 *)bank)[context->index];
    context->position = 0;
    if ((u8)func_0800A154(context) == 1)
        result = g_state_02000000[0x219C];
    return result;
}
