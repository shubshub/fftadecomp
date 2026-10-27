#include "ffta.h"

typedef struct Object Object;

typedef struct {
    const Object *source;
    const Object *target;
    u32 unknown_08;
    u16 first;
    u16 second;
    u8 unknown_10[0x16];
    u16 flags;
} ComparisonContext;

extern s32 func_0813054C(const Object *source, const Object *target,
                        u32 first, u32 second, u8 mode);

/* Target: [0x08131804, 0x08131836), 50 bytes, 24 instructions. */
s32 func_08131804(const ComparisonContext *context)
{
    const Object *source = context->source;
    const Object *target = context->target;
    u32 first = context->first;
    u32 second = context->second;
    u16 mode = context->flags & 0x10;

    if (mode)
        mode = 2;
    return func_0813054C(source, target, first, second, mode);
}
