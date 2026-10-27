#include "ffta.h"

typedef struct {
    u8 unknown_00[0xD6];
    u16 value;
} Unit;

typedef struct {
    Unit *source;
    Unit *target;
    u8 unknown_08[0x1E];
    u16 flags;
} Context;

extern u32 func_08131B20(void);

/* Complete [0x08133724, 0x08133756): 50 bytes, 24 instructions. */
void func_08133724(Context *context)
{
    if ((context->flags & 0x10) == 0) {
        context->source->value += func_08131B20();
        if (context->target->value > 10)
            context->target->value = 10;
    }
}
