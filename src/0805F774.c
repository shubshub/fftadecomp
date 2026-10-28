#include "ffta.h"

struct Control0805F774 {
    u8 unknown_00[0x11];
    u8 current;
    u8 unknown_12[8];
    s16 position;
    u8 unknown_1C[4];
};

struct State0805F774 {
    u8 slot;
    s8 step;
    u8 unknown_02[0x3A];
    struct Control0805F774 primary;
    struct Control0805F774 secondary;
};

struct Selection0805F774 {
    s16 position;
    u16 current;
};

struct SelectionState0805F774 {
    u8 unknown_000[0x128];
    struct Selection0805F774 selections[1];
};

extern struct SelectionState0805F774 *data_0200F44C;
extern s16 func_08017BE8(struct Control0805F774 *control);
extern void func_08141540(u32 sound);
extern void func_0806025C(struct State0805F774 *state);

/* Complete [0x0805F774, 0x0805F822): 174 bytes, 81 instructions. */
void func_0805F774(struct State0805F774 *state, u8 direction)
{
    struct Control0805F774 *primary = &state->primary;
    struct Control0805F774 *secondary = &state->secondary;
    struct Selection0805F774 *selection = &data_0200F44C->selections[state->slot];
    s32 initial = primary->position;
    s32 position = initial;
    s32 count = func_08017BE8(primary) + 1;
    s32 current = secondary->current;
    s32 remaining = state->step;

    while (remaining != 0) {
        remaining--;
        if (direction == 0x80) {
            if (position + state->step < count) {
                position++;
            } else {
                remaining = 0;
                if (initial == count - state->step)
                    current = state->step - 1;
            }
        } else {
            if (position > 0) {
                position--;
            } else {
                remaining = 0;
                if (initial == 0)
                    current = 0;
            }
        }
    }
    if (initial != position || secondary->current != current) {
        selection->position = position;
        selection->current = current;
        func_08141540(0x6D);
        func_0806025C(state);
    }
}
