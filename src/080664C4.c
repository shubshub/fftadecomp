#include "ffta.h"

/* Complete [0x080664C4, 0x080664DE): 26 bytes, 12 instructions. */
typedef struct {
    u8 unknown_00[0xa0];
    void *allocation;
} AllocationState;

extern void func_08005B40(void *);

void func_080664C4(AllocationState *state)
{
    if (state->allocation) {
        func_08005B40(state->allocation);
        state->allocation = 0;
    }
}
