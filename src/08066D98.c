#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u8 id;
    u8 flags;
} State08066D98;

extern u8 func_080099A4(u8);
extern void func_0806707C(State08066D98 *);

/* Complete [0x08066D98, 0x08066DC2): 42 bytes, 19 instructions. */
u8 func_08066D98(State08066D98 *state)
{
    u32 result;

    if (!func_080099A4(state->id)) {
        result = 0;
    } else {
        state->flags |= 4;
        func_0806707C(state);
        result = 1;
    }
    return result;
}
