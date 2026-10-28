#include "ffta.h"

/* Complete [0x08070120, 0x0807016E): 78 bytes, 37 instructions. */
typedef struct {
    u16 *tiles;
    u8 unknown_04[0xc];
    u8 x;
    u8 y;
    u8 unknown_12[4];
    u8 stride;
} ValueDisplay;

extern void func_0802ACA0(u16 *, u16, u8, u8);

void func_08070120(ValueDisplay *state, u16 first, u16 second)
{
    func_0802ACA0(state->tiles + (state->stride * (state->y + 1) + state->x + 13),
                  first, 12, 3);
    func_0802ACA0(state->tiles + (state->stride * (state->y + 1) + state->x + 17),
                  second, 12, 3);
}
