#include "control_flags.h"

typedef struct {
    s16 time;
    u8 first;
    u8 second;
} BlendKeyframe;

typedef struct {
    BlendKeyframe keys[2];
    s16 cursor;
} BlendState;

extern BlendState *func_0804CAB0(void);

u8 func_0804DF08(void)
{
    BlendState *blend = func_0804CAB0();
    BlendKeyframe *current;
    BlendKeyframe *next;
    s32 index;

    for (index = 0; ; index++) {
        next = index + 1 < 2 ? &blend->keys[index + 1] : 0;
        current = &blend->keys[index];
        if (next == 0)
            break;
        if (current->time <= blend->cursor && blend->cursor < next->time)
            break;
    }
    if (current != 0) {
        if (next == 0) {
            g_control_flags_03000940.bldalpha_lo = current->first;
            g_control_flags_03000940.bldalpha_hi = current->second;
        } else {
            s16 elapsed = blend->cursor - current->time;
            s16 duration = next->time - current->time;
            s16 first_delta = next->first - current->first;
            s16 second_delta = next->second - current->second;

            g_control_flags_03000940.bldalpha_lo =
                current->first + first_delta * elapsed / duration;
            g_control_flags_03000940.bldalpha_hi =
                current->second + second_delta * elapsed / duration;
        }
    }
    blend->cursor++;
    if (next == 0)
        return 1;
    return 0;
}
