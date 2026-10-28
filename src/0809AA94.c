#include "ffta.h"

typedef struct {
    void *unit;
    u8 unknown_04[0x7c];
    void *owner;
} Context0809AA94;

typedef struct {
    u32 first;
    u32 second;
} Parameters0809AA94;

extern u32 func_08098E7C(void *owner, void *unit, u32 first, u32 second,
                       u32 value, u32 mode);

/* Complete [0x0809AA94, 0x0809AAC6): 50 bytes, 24 instructions. */
u32 func_0809AA94(Context0809AA94 *context, const Parameters0809AA94 *parameters,
                  u32 value, u32 mode)
{
    return func_08098E7C(context->owner, context->unit,
                         parameters->first, parameters->second, value, mode);
}
