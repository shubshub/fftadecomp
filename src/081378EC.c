#include "ffta.h"

/* Complete [0x081378EC, 0x0813790A): 30 bytes, 13 instructions. */
typedef struct {
    void *resource;
    u8 enabled;
} ResourceState;

extern u32 func_0814846C(void *resource);
extern void func_08148498(void *resource);

void func_081378EC(ResourceState *state)
{
    state->enabled = 0;
    if (func_0814846C(state->resource))
        func_08148498(state->resource);
}
