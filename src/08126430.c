#include "control_flags.h"

typedef struct {
    u8 unknown_00[5];
    s8 direction;
    u8 unknown_06;
    u8 brightness;
} State08126430;

extern u8 func_08121E3C(void);
extern void func_08121E30(u8 value);

/* Complete [0x08126430, 0x081264B8): 136 bytes including literal pools. */
void func_08126430(State08126430 *state)
{
    s32 direction;
    u8 level;

    g_control_flags_03000940.bldcnt_lo = 0x3F;
    direction = state->direction;
    if (direction < 0)
        direction = -direction;
    if (direction <= 1)
        g_control_flags_03000940.bldcnt_lo |= 0x80;
    else
        g_control_flags_03000940.bldcnt_lo |= 0xC0;
    level = func_08121E3C();
    if (state->direction > 0) {
        if (level == 0)
            level = 100;
    } else {
        if (level == 100)
            level = 0;
    }
    func_08121E30(level);
    state->brightness = (g_control_flags_03000940.bldy_lo = ((100 - level) * 16) / 100);
    g_control_flags_03000940.bldcnt_hi = 0;
}
