#include "control_flags.h"

typedef struct {
    u8 mode;
    u8 unknown_01;
    u16 elapsed;
    u16 duration;
    u8 first;
    u8 last;
} BrightnessTransition;

/* The interpolation at 0x0813EB7A repeats func_081369B0. */
static inline s16 interpolate(s16 first, s16 last, u16 duration, u16 elapsed)
{
    if (elapsed >= duration)
        return last;
    first += (last - first) * elapsed / duration;
    return first;
}

/* Complete target: [0x0813EB64, 0x0813EBB2), 78 bytes. */
void func_0813EB64(BrightnessTransition *state)
{
    switch (state->mode) {
    case 0:
        break;
    case 1:
        g_control_flags_03000940.bldy_lo = interpolate(state->first, state->last,
                                                      state->duration, state->elapsed);
        if (state->duration <= state->elapsed)
            state->mode = 0;
        else
            state->elapsed++;
        break;
    }
}
