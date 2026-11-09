#include "control_flags.h"

/* 0x0813F140..0x0813F19C: 92 bytes. */
typedef struct {
    u8 active;
    u8 unknown_01;
    u16 elapsed;
    u16 duration;
    u8 first;
    u8 last;
} Transition;

void func_0813F140(Transition *state, u8 first, u8 last,
                   u16 mode, u16 duration)
{
    if (duration == 0) {
        state->active = 0;
        g_control_flags_03000940.bldcnt_lo = mode;
        g_control_flags_03000940.bldy_lo = first;
    } else {
        state->first = first;
        state->last = last;
        state->elapsed = 0;
        state->duration = duration;
        g_control_flags_03000940.bldcnt_lo = mode;
        g_control_flags_03000940.bldy_lo = first;
        state->active = 1;
    }
}
