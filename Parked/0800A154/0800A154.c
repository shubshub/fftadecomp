#include "ffta.h"

typedef struct ScriptContext {
    u8 bank;
    u8 index;
    s16 position;
    const u8 *script;
} ScriptContext;

typedef u32 (*ScriptHandler)(ScriptContext *context, const u8 *instruction);

extern const u8 g_table_0836D5A4[][6];

u32 func_0800A154(ScriptContext *context)
{
    const u8 (*entries)[6] = g_table_0836D5A4;

    for (;;) {
        const u8 *instruction = context->script + context->position;
        u8 opcode = *instruction;
        const u8 *entry;
        ScriptHandler handler;
        u16 length;

        if (opcode == 0)
            return 1;
        entry = entries[opcode];
        handler = (ScriptHandler)((u32)entry[2] | ((u32)entry[3] << 8) |
                                  ((u32)entry[4] << 16) | ((u32)entry[5] << 24));
        handler(context, instruction);
        length = entry[0] | (entry[1] << 8);
        context->position = length + (u16)context->position;
    }
}
