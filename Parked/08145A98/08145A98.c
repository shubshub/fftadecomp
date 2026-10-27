#include "ffta.h"

struct AudioTrack08145A98 {
    u8 flags;
    u8 unknown_01[7];
    s8 key;
    u8 pitch;
    s8 key_shift;
    s8 key_shift_extra;
    s8 tune;
    u8 pitch_delta;
    s8 bend;
    u8 bend_range;
    u8 volume_left;
    u8 volume_right;
    u8 volume;
    u8 volume_scale;
    s8 pan;
    s8 pan_extra;
    s8 modulation;
    u8 unknown_17;
    u8 modulation_type;
};

/* Complete [0x08145A98, 0x08145B4C): 180 bytes, 90 instructions. */
void func_08145A98(void *player, struct AudioTrack08145A98 *track)
{
    s32 value;
    u32 volume;
    u32 scale;
    u32 level;

    if (track->flags & 1) {
        scale = track->volume_scale;
        level = track->volume;
        volume = (scale * level) >> 5;
        if (track->modulation_type == 1)
            volume = ((track->modulation + 128) * volume) >> 7;
        value = track->pan * 2 + track->pan_extra;
        if (track->modulation_type == 2)
            value += track->modulation;
        if (value < -128)
            value = -128;
        else if (value > 127)
            value = 127;
        track->volume_left = ((value + 128) * volume) >> 8;
        track->volume_right = ((127 - value) * volume) >> 8;
    }
    if (track->flags & 4) {
        value = track->bend;
        value = track->bend_range * value;
        value = track->tune + value;
        value = value * 4 + track->key_shift * 256
              + track->key_shift_extra * 256;
        value = track->pitch_delta + value;
        if (track->modulation_type == 0)
            value += track->modulation * 16;
        track->key = value >> 8;
        track->pitch = value;
    }
    track->flags &= ~5;
}
