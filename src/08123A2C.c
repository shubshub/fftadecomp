#include "ffta.h"

typedef struct {
    u32 unknown_00;
    u16 countdown;
} ScriptContext;

u8 func_080C95A8(u16 index);
void func_080C95C0(u16 index, u32 value);
void func_080C7378(void);

u32 func_08123A2C(ScriptContext *context, const u8 *script)
{
    u32 result;

    if (func_080C95A8(13) != 1)
        result = 0x110;
    else {
        func_080C95C0(13, 0);
        context->countdown = 16;
        func_080C7378();
        result = 0x11B;
    }
    return result;
}
