#include "ffta.h"

typedef struct Object Object;

typedef struct {
    const Object *source;
    const Object *target;
} ObjectPair;

extern u32 func_0812F0CC(const void *unit, u16 *output);
extern u8 func_08131160(const ObjectPair *context);

/* 0x081311DC..0x08131204, 40 bytes. The collector expects at most two qualifying items. */
u8 func_081311DC(const ObjectPair *context)
{
    u16 selected[2];

    if (!func_0812F0CC(context->target, selected))
        return 0;
    return func_08131160(context);
}
