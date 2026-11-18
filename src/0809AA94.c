#include "ffta.h"

typedef struct {
    void *unit;
    u8 unknown_04[0x7c];
    void *owner;
} Context0809AA94;

typedef struct {
    void *target;
    void *related;
} Parameters0809AA94;

extern u32 func_08098E7C(void *owner, void *unit, void *target, void *related,
                         u8 *x, u8 *y);

/* Complete [0x0809AA94, 0x0809AAC6): 50 bytes, 24 instructions. */
u32 func_0809AA94(Context0809AA94 *context, const Parameters0809AA94 *parameters,
                  u8 *x, u8 *y)
{
    return func_08098E7C(context->owner, context->unit,
                         parameters->target, parameters->related, x, y);
}
