#include "ffta.h"

typedef struct {
    u32 selector : 8;
    u32 mode : 8;
    s32 x : 16;
    s32 y : 16;
    u32 value : 16;
} ScriptArguments;

void func_08127C10(void *context, ScriptArguments arguments);
void func_08127BC4(void *context, ScriptArguments arguments);

u32 func_08122770(void *context, const u8 *script)
{
    ScriptArguments arguments;

    arguments.selector = script[1];
    arguments.x = script[2] | script[3] << 8;
    arguments.y = script[4] | script[5] << 8;
    arguments.mode = script[6];
    arguments.value = script[8] | script[9] << 8;
    if (script[7] == 1)
        func_08127C10(context, arguments);
    else
        func_08127BC4(context, arguments);
    return 0x115;
}
