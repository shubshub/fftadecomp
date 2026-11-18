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
extern u8 func_08131030(u32 unit);

/* Evaluator slot 39, [0x081319FC, 0x08131A50). */
s32 func_081319FC(const Context *context)
{
    s32 value = func_0813189C(context);
    u32 limit;

    if (value < 0)
        value = 0;
    if (func_08131030((u32)context->target))
        value = -value;
    limit = func_080C7EA4(context->target, 0x13);
    if (limit < (u32)(value < 0 ? -value : value)) {
        if (value < 0)
            value = -func_080C7EA4(context->target, 0x13);
        else
            value = func_080C7EA4(context->target, 0x13);
    }
    return value;
}
