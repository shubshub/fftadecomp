#include "ffta.h"

/* Complete [0x0806F0DC, 0x0806F1EC): 272 bytes, 126 instructions. */
typedef struct {
    s8 x;
    s8 y;
    u8 active;
    u8 unknown_03;
    u16 entry;
} ValueDisplay;

extern s32 func_080CA7A4(u16, u8);
extern void func_0806F568(s16, s16, u8, u16);

void func_0806F0DC(ValueDisplay *state)
{
    if (state->active) {
        func_0806F568(state->x * 8 + 80, state->y * 8 + 4, 3,
                      func_080CA7A4(state->entry, 10));
        func_0806F568(state->x * 8 + 80, state->y * 8 + 16, 3,
                      func_080CA7A4(state->entry, 11));
        func_0806F568(state->x * 8 + 80, state->y * 8 + 28, 3,
                      func_080CA7A4(state->entry, 12));
        func_0806F568(state->x * 8 + 80, state->y * 8 + 40, 3,
                      func_080CA7A4(state->entry, 13));
        func_0806F568(state->x * 8 + 80, state->y * 8 + 52, 3,
                      func_080CA7A4(state->entry, 14));
    }
}
