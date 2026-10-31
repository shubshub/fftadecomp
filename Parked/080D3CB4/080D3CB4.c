#include "ffta.h"

typedef struct {
    u16 control;
    u16 values;
    u16 count;
} __attribute__((packed)) Sequence;

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct {
    const Sequence *sequence;
    u8 flags;
    u8 mode;
    u8 control;
    u8 control_high;
    u8 first;
    u8 second;
    u16 delay;
    u16 index;
    u16 first_duration;
    u16 second_duration;
    u8 unknown_12[2];
    InterpolationState first_transition;
    InterpolationState second_transition;
} State;

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    const Sequence *sequence;
    u8 unknown_08[12];
    u16 flags;
    u16 delay;
} Descriptor;

typedef struct {
    u8 unknown_00[0x4A];
    u8 control;
    u8 control_high;
    u8 first;
    u8 second;
    u8 third;
} Control;

extern Control g_control_flags_03000940;
extern void func_080D3BD0(State *state);
extern void func_080E064C(InterpolationState *state);
extern u8 func_080E0690(InterpolationState *state);

/* 0x080D3CB4..0x080D3E9C, 488 bytes.
 * Target:
 * f0b557464e464546e0b40e1c151c3188012900d1dee0012902dc002908d0d9e0
 * 8020400081422dd00130814248d0d1e072682a60b08a2871f08a013068811178
 * 507800020843c0210840800968711078a8711178507800020843fc239b01191c
 * 0840000ae87190781f21084028729178d07800020843f8225201111c0840000a
 * 6872a7e06889013868810004002800d0a0e00a4a68798001a9790843131c4a33
 * 19781870e8794b3211781070281cfff735ff3088013030808ce0000040090003
 * 297980200840002800d083e02f7a6b7a9a46002080468146e889002807d00138
 * e881000400281fd1012290461ce02c1c1434201c0cf050fc6879012806d10248
 * a98a4c3005e00000400900030c48a98a4e3002780170201c0cf060fc00060028
 * 01d0012398462f7d288a00280ad001382882000400281bd10120814618e00000
 * 400900032c1c2034201c0cf025fc1748298c4d3002780170201c0cf03ffc0006
 * 002801d001229146288c0006000e82462f7253466b72404600282bd04a46002a
 * 28d0a8890130a88129680a79497909020004000c114388420cd3297901200840
 * 002805d00020a88104e0000040090003022030803188022903d0281cfff7aefe
 * 08e028790140002904d006484a30017800210170002038bc9846a146aa46f0bc
 * 02bc084740090003
 */
u32 func_080D3CB4(void *task, void *descriptor, void *payload)
{
    Descriptor *desc = descriptor;
    State *state = payload;

    switch (desc->phase) {
    case 0:
        state->sequence = desc->sequence;
        state->flags = desc->flags;
        state->delay = desc->delay + 1;
        state->mode = (state->sequence->control & 0xC0) >> 6;
        state->control = state->sequence->control;
        state->control_high = (state->sequence->control & 0x3F00) >> 8;
        state->first = state->sequence->values & 0x1F;
        state->second = (state->sequence->values & 0x1F00) >> 8;
        break;

    case 0x100:
        state->delay--;
        if (state->delay == 0) {
            g_control_flags_03000940.control = (state->mode << 6) | state->control;
            g_control_flags_03000940.control_high = state->control_high;
            func_080D3BD0(state);
            desc->phase++;
        }
        break;

    case 0x101:
        if (!(state->flags & 0x80)) {
            u8 first = state->first;
            u8 second = state->second;
            int first_done = 0;
            int second_done = 0;

            if (state->first_duration != 0) {
                state->first_duration--;
                if (state->first_duration == 0)
                    first_done = 1;
            } else {
                func_080E064C(&state->first_transition);
                if (state->mode == 1)
                    g_control_flags_03000940.first = state->first_transition.current;
                else
                    g_control_flags_03000940.third = state->first_transition.current;
                if (func_080E0690(&state->first_transition))
                    first_done = 1;
                first = state->first_transition.current;
            }

            if (state->second_duration != 0) {
                state->second_duration--;
                if (state->second_duration == 0)
                    second_done = 1;
            } else {
                func_080E064C(&state->second_transition);
                g_control_flags_03000940.second = state->second_transition.current;
                if (func_080E0690(&state->second_transition))
                    second_done = 1;
                second = state->second_transition.current;
            }

            state->first = first;
            state->second = second;
            if (first_done && second_done) {
                state->index++;
                if (state->index >= state->sequence->count) {
                    if (state->flags & 1)
                        state->index = 0;
                    else
                        desc->phase = 2;
                }
                if (desc->phase != 2)
                    func_080D3BD0(state);
                else if (state->flags & 2)
                    g_control_flags_03000940.control = 0;
            }
        }
        break;
    }
    return 0;
}
