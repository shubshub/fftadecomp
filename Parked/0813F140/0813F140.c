#include "ffta.h"

/* 0x0813F140..0x0813F19C: 92 bytes. */
typedef struct {
    u8 active;
    u8 unknown_01;
    u16 elapsed;
    u16 duration;
    u8 first;
    u8 last;
} Transition;

typedef struct {
    u8 unknown_00[0x4A];
    u16 mode : 8;
    u16 unknown_4B : 8;
    u8 unknown_4C[2];
    u16 value : 8;
    u16 unknown_4F : 8;
} ControlState;

extern ControlState g_control_flags_03000940;

void func_0813F140(Transition *state, u8 first, u8 last,
                   u16 mode, u16 duration)
{
    if (duration == 0) {
        ControlState *control;
        state->active = 0;
        control = &g_control_flags_03000940;
        control->mode = mode;
        control->value = first;
    } else {
        ControlState *control;
        state->first = first;
        state->last = last;
        state->elapsed = 0;
        state->duration = duration;
        control = &g_control_flags_03000940;
        control->mode = mode;
        control->value = first;
        state->active = 1;
    }
}
