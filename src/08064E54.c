#include "ffta.h"

typedef struct {
    u8 unknown_00[0x3C28];
    u16 index;
} State;

extern u8 g_state_02000000[];

u32 func_080CE4DC(u16 index, u8 selector);

u8 func_08064E54(void)
{
    State *state = (State *)g_state_02000000;

    return func_080CE4DC(state->index, 0x12) == 2;
}
