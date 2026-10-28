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

extern s32 func_0813079C(void *source, void *target, u16 entry,
                         u16 first, u16 second, u8 mode);

/* Complete [0x0813189C, 0x081318D2): 54 bytes, 26 instructions. */
s32 func_0813189C(const Context *context)
{
    return func_0813079C(context->source, context->target, context->entry,
                         context->first, 0, (u16)(context->flags & 0x10) ? 2 : 0);
}
