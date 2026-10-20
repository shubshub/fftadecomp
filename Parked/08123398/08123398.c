#include "ffta.h"

typedef struct {
    u32 selector : 8;
    u32 mode : 8;
    s16 x;
    s16 y;
    u16 amount;
} ScriptParameters;

void func_08124E74(u8 selector, s8 x, s8 y, s16 *resolved_x, s16 *resolved_y);
void func_08127B80(void *context, ScriptParameters parameters);

u32 func_08123398(void *context, const u8 *script)
{
    ScriptParameters parameters;

    parameters.selector = script[1];
    func_08124E74(parameters.selector, (s8)script[2], (s8)script[3],
                 &parameters.x, &parameters.y);
    parameters.mode = script[4];
    parameters.amount = script[5] | (script[6] << 8);
    func_08127B80(context, parameters);
    return 0x115;
}
