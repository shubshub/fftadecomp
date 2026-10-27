#include "ffta.h"

struct State08021C90 {
    u8 unknown_00[0xC];
    u16 first;
    u16 last;
    u16 alternate_first;
    u16 alternate_last;
};

extern s32 func_080213DC(struct State08021C90 *state, s32 step,
                        s32 first, s32 last);

s32 func_08021C90(struct State08021C90 *state, u32 alternate, s32 step)
{
    u16 first;
    u16 last;

    if (alternate == 0) {
        first = state->first;
        last = state->last;
    } else {
        first = state->alternate_first;
        last = state->alternate_last;
    }
    return func_080213DC(state, step, first, last);
}
