#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u32 value;
} Context08099CD0;

extern u32 func_080C7B08(u32 value);

/* Complete [0x08099CD0, 0x08099CDC): 12 bytes, 5 instructions. */
u32 func_08099CD0(Context08099CD0 *context)
{
    return func_080C7B08(context->value);
}
