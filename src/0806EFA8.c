#include "ffta.h"

/* 0x0806EFA8..0x0806EFE4: 60 bytes. */
typedef struct {
    u8 selection;
    u8 unknown_01[6];
    u8 count;
} MenuSelection;

extern void func_0806EE98(MenuSelection *state);

void func_0806EFA8(MenuSelection *state, u16 input)
{
    switch (input) {
    case 0x20:
        if (state->selection == 0)
            state->selection = state->count - 1;
        else
            --state->selection;
        break;
    case 0x10:
        if (state->selection == state->count - 1)
            state->selection = 0;
        else
            ++state->selection;
        break;
    }
    func_0806EE98(state);
}
