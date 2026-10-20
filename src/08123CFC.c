#include "ffta.h"

typedef struct {
    u16 offset;
} ScriptContext;

u8 func_080C95A8(u16 index);

u32 func_08123CFC(ScriptContext *context, const u8 *script)
{
    if (func_080C95A8(13) == 1) {
        u32 displacement = script[1] | (script[2] << 8);
        context->offset += displacement;
    }

    return 0x110;
}
