#include "ffta.h"

struct State08009C94 {
    u8 unknown_00[0x28];
    u16 input;
    u8 unknown_2A[0x3B7A];
    u32 flags;
};

extern struct State08009C94 g_state_02000080;
extern u8 func_080C8348(struct State08009C94 *state);
extern u8 func_080C8364(struct State08009C94 *state);
extern void func_08009AFC(u16 value);

/* Complete [0x08009C94, 0x08009CE0): 76 bytes, 31 instructions. */
u8 func_08009C94(void)
{
    struct State08009C94 *state = &g_state_02000080;

    if ((state->input & 0x81) &&
        (func_080C8348(state) || func_080C8364(state))) {
        func_08009AFC(0xAA);
        state->flags |= 4;
        return 1;
    }
    return 0;
}
