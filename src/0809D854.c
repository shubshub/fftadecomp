#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1c];
    u8 active;
} Context0809D854;

extern void func_0809C6B8(u8 selector, Context0809D854 *context, u32 value);

/* Complete [0x0809D854, 0x0809D86C): 24 bytes, 11 instructions. */
void func_0809D854(Context0809D854 *context, u32 selector, u32 value)
{
    context->active = 0;
    func_0809C6B8(selector, context, value);
}
