#include "ffta.h"

/* Complete [0x08066570, 0x080665AE): 62 bytes, 28 instructions. */
typedef struct {
    u8 unknown_00[9];
    u8 status;
    u8 unknown_0a[0x8e];
    void *allocation_98;
    void *allocation_9c;
} AllocationState;

extern u8 func_080099A4(u8);
extern void func_08005B40(void *);

u8 func_08066570(AllocationState *state)
{
    if (func_080099A4(state->status)) {
        if (state->allocation_9c) {
            func_08005B40(state->allocation_9c);
            state->allocation_9c = 0;
        }
        if (state->allocation_98) {
            func_08005B40(state->allocation_98);
            state->allocation_98 = 0;
        }
        return 1;
    }
    return 0;
}
