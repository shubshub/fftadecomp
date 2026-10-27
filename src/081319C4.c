#include "ffta.h"

typedef struct Unit Unit;

typedef struct {
    const Unit *source;
    const Unit *target;
    u32 unknown_08;
    u16 identifier;
    u16 value;
    u8 unknown_10[0x16];
    u16 flags;
} ComparisonContext;

extern s32 func_081307F4(const Unit *source, const Unit *target,
                        u32 identifier, u32 value, u16 parameter, u8 option);

/* Target: [0x081319C4, 0x081319FA), 54 bytes, 26 instructions. */
s32 func_081319C4(const ComparisonContext *context)
{
    const Unit *source = context->source;
    const Unit *target = context->target;
    u32 identifier = context->identifier;
    u32 value = context->value;

    return func_081307F4(source, target, identifier, value, 0,
                         (u16)(context->flags & 0x10) ? 2 : 0);
}
