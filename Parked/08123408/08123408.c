#include "ffta.h"

typedef struct {
    u32 selector : 8;
    u32 mode : 8;
    s16 x;
    s16 y;
    u16 amount;
} ScriptParameters;

void func_08124E74(u8 selector, s8 x, s8 y, s16 *screen_x, s16 *screen_y);
void func_08127C10(void *context, ScriptParameters parameters);
void func_08127BC4(void *context, ScriptParameters parameters);

u32 func_08123408(void *context, const u8 *script)
{
    ScriptParameters parameters;

    parameters.selector = script[1];
    func_08124E74(parameters.selector, (s8)script[2], (s8)script[3],
                  &parameters.x, &parameters.y);
    parameters.mode = script[4];
    parameters.amount = script[6] | (script[7] << 8);
    if (script[5] == 1)
        func_08127C10(context, parameters);
    else
        func_08127BC4(context, parameters);
    return 0x115;
}
