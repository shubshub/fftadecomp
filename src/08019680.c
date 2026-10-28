#include "ffta.h"

/* 0x08019680..0x080196B0: 48 bytes / 20 instructions. */
typedef struct {
    u8 unknown_00[0x16];
    u8 count;
} CountState;

extern CountState *g_state_020020D0;
extern u16 func_08018CB8(u8 *destination, s8 width);
extern u16 func_08018ABC(u8 *destination, u32 value);

u32 func_08019680(u8 *destination)
{
    CountState *state = g_state_020020D0;
    u8 *cursor = destination;

    if (state->count < 10)
        cursor += func_08018CB8(cursor, 8);
    func_08018ABC(cursor, state->count);
    return 0;
}
