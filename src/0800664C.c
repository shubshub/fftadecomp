#include "control_flags.h"

/* Complete [0x0800664C, 0x08006720): 212 bytes, 97 instructions. */

typedef struct TransitionState {
    u16 first;
    u16 second;
    u16 target_first;
    u16 target_second;
    u16 step_first;
    u16 step_second;
    s16 delta_first;
    s16 delta_second;
    s16 error;
    s16 half_second;
    s16 remaining;
} TransitionState;

typedef struct TransitionEvent {
    u16 state;
    u8 unknown_02[0x12];
    u16 initial;
    u16 target;
    s16 duration;
} TransitionEvent;

typedef struct TransitionPayload {
    u8 initial_first;
    u8 initial_second;
    u8 target_first;
    u8 target_second;
    s16 duration;
    u8 unknown_06[2];
    TransitionState channels[2];
} TransitionPayload;

void func_08007620(void *state, u16 first, u16 second,
                   u16 target_first, s16 duration);
void func_080076F4(void *state);
u32 func_08007894(const void *state);

u32 func_0800664C(void *task, TransitionEvent *event, TransitionPayload *payload)
{
    switch (event->state) {
    case 0:
        payload->initial_first = event->initial >> 8;
        payload->initial_second = event->initial;
        payload->target_first = event->target >> 8;
        payload->target_second = event->target;
        payload->duration = event->duration;
        break;
    case 1:
        break;
    case 0x100:
        g_control_flags_03000940.bldalpha_lo = payload->initial_first;
        g_control_flags_03000940.bldalpha_hi = payload->initial_second;
        func_08007620(&payload->channels[0], payload->initial_first, 0,
                       payload->target_first, payload->duration);
        func_08007620(&payload->channels[1], payload->initial_second, 0,
                       payload->target_second, payload->duration);
        event->state++;
        /* fall through */
    case 0x101:
        func_080076F4(&payload->channels[0]);
        func_080076F4(&payload->channels[1]);
        g_control_flags_03000940.bldalpha_lo = payload->channels[0].first;
        g_control_flags_03000940.bldalpha_hi = payload->channels[1].first;
        if (func_08007894(&payload->channels[0]) != 0 &&
            func_08007894(&payload->channels[1]) != 0) {
            event->state = 2;
        }
        break;
    }
    return 0;
}
