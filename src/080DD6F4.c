#include "ffta.h"

typedef struct {
    const void *unit;
} UnitContext;

extern s32 func_080C7EA4(const void *object, u32 selector);

/* 080DD6F4..080DD706: 18 bytes. */
u16 func_080DD6F4(const UnitContext *context)
{
    return func_080C7EA4(context->unit, 3);
}
