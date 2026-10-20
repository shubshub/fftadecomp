#include "ffta.h"

typedef struct {
    u16 offset;
} ScriptContext;

s8 func_08013380(void);

u32 func_08123D28(ScriptContext *context, const u8 *script)
{
    if (func_08013380() == 0) {
        u32 displacement = script[1] | (script[2] << 8);

        context->offset += displacement;
    }
    return 0x110;
}
