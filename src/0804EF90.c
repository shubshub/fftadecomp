#include "ffta.h"

typedef struct {
    u8 unknown_00[9];
    u8 selector;
    u8 unknown_0A[0x86];
    void *primary;
    void *secondary;
} State0804EF90;

extern u8 func_080099A4(u8 selector);
extern void func_08005B40(void *object);

/* Complete [0x0804EF90, 0x0804EFCE): 62 bytes, 28 instructions. */
u8 func_0804EF90(State0804EF90 *state)
{
    if (func_080099A4(state->selector)) {
        if (state->secondary) {
            func_08005B40(state->secondary);
            state->secondary = 0;
        }
        if (state->primary) {
            func_08005B40(state->primary);
            state->primary = 0;
        }
        return 1;
    }
    return 0;
}
