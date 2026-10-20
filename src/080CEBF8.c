#include "ffta.h"

typedef struct {
    u8 unknown_00[0x3C28];
    u16 index;
} State;

extern u8 g_state_02000000[];

u32 func_080CE4DC(u16 index, u8 selector);

u8 func_080CEBF8(u8 mode)
{
    if (mode == 0) {
        State *state = (State *)g_state_02000000;
        u16 index = state->index;
        u8 result;

        if (index == 0)
            return 6;
        result = func_080CE4DC(index, 2);
        result += 15;
        if (func_080CE4DC(state->index, 1) == 1)
            result = 6;
        return result;
    }
    if (mode == 1) {
        State *state = (State *)g_state_02000000;
        u8 result;

        result = func_080CE4DC(state->index, 2);
        result += 15;
        if (func_080CE4DC(state->index, 1) == 1)
            result = 6;
        return result;
    }
    return 6;
}
