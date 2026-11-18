#include "ffta.h"

typedef struct {
    void *source;
    void *target;
    u8 unknown_08[4];
    u16 entry;
    u16 first;
    u8 unknown_10[0x16];
    u16 flags;
} Context;

extern s32 func_0813189C(const Context *context);
extern s32 func_080C7EA4(const void *object, u32 selector);

/* Evaluator slot 33, [0x08131930, 0x0813195A). */
s32 func_08131930(const Context *context)
{
    s32 value = func_0813189C(context);

    if (func_080C7EA4(context->target, 0x15) - value < 0)
        value = func_080C7EA4(context->target, 0x15);
    return value;
}
