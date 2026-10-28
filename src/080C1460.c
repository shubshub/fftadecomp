#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x54EC];
    u8 *allocation;
} State080C1460;

extern State080C1460 data_020101F8;
extern void func_08022854(u8 *object);

/* Complete [0x080C1460, 0x080C1484): 36 bytes, 13 instructions. */
void func_080C1460(void)
{
    State080C1460 *state = &data_020101F8;

    if (state->allocation != 0) {
        func_08022854(state->allocation);
        state->allocation = 0;
    }
}
