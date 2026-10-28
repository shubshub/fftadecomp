#include "ffta.h"

/* 0x081459D0..0x08145A98: 200 bytes, including the literal pool. */
typedef struct {
    u8 flags;
    u8 unknown_01[0x12];
    u8 volume;
    u8 unknown_14[0x3C];
} FadeChannel;

typedef struct {
    u32 unknown_00;
    u32 flags;
    u8 channel_count;
    u8 unknown_09[0x1B];
    u16 period;
    u16 timer;
    u16 level;
    u16 unknown_2A;
    FadeChannel *channels;
} FadeState;

extern void func_08144D94(FadeState *, FadeChannel *);

void func_081459D0(FadeState *state)
{
    int count;
    FadeChannel *channel;
    u16 level;

    if (state->period == 0)
        return;
    if (--state->timer != 0)
        return;
    state->timer = state->period;

    if (state->level & 2) {
        if ((state->level += 0x10) > 0xFF) {
            state->level = 0x100;
            state->period = 0;
        }
    } else {
        if ((s16)(state->level -= 0x10) <= 0) {
            count = state->channel_count;
            channel = state->channels;
            for (; count > 0; --count, ++channel) {
                func_08144D94(state, channel);
                level = state->level;
                if (!(1 & level))
                    channel->flags = 0;
            }
            if (1 & state->level)
                state->flags |= 0x80000000;
            else
                state->flags = 0x80000000;
            state->period = 0;
            return;
        }
    }

    count = state->channel_count;
    channel = state->channels;
    for (; count > 0; --count, ++channel) {
        if (channel->flags & 0x80) {
            level = state->level;
            channel->volume = level >> 2;
            channel->flags |= 3;
        }
    }
}
