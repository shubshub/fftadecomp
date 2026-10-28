#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u16 item;
} State0806F3C4;

/* Complete [0x0806F3C4, 0x0806F3C8): 4 bytes, 2 instructions. */
void func_0806F3C4(State0806F3C4 *state, u16 item)
{
    state->item = item;
}
