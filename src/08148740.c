#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u16 flags;
    u8 unknown_04[0xC];
    u8 phase;
} UpdateState;

extern void func_081465E8(UpdateState *state);

void func_08148740(UpdateState *state)
{
    if (state->flags & 0x20) {
        if (state->flags & 0x780) {
            state->phase++;
            if (!(state->flags & (0x80 << (state->phase & 3))))
                return;
        } else {
            state->flags ^= 0x40;
            if (state->flags & 0x40)
                return;
        }
    }

    func_081465E8(state);
}
