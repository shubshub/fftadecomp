#include "ffta.h"

typedef struct MusicPlayer MusicPlayer;

/* The song_* members are set by the sequence's own commands (m4a_1.s
 * ply_keysh, ply_vol, ply_pan: strb at 0x08144A12, 0x08144A56, 0x08144A6C);
 * key_shift and pitch by src/08146188.c (0x081461D2, 0x081461D4), volume by
 * src/08146120.c (0x08146162) and pan by src/081461FC.c (0x0814623E). */
typedef struct {
    u8 flags;
    u8 unknown_01[7];
    u8 key_calculated;
    u8 pitch_calculated;
    s8 song_key_shift;
    s8 key_shift;
    s8 tune;
    u8 pitch;
    s8 bend;
    u8 bend_range;
    u8 volume_right;
    u8 volume_left;
    u8 song_volume;
    u8 volume;
    s8 song_pan;
    s8 pan;
    s8 modulation;
    u8 unknown_17;
    u8 modulation_type;
} MusicPlayerTrack;

/* Complete [0x08145A98, 0x08145B4C): 180 bytes, 90 instructions.
 * m4a.c TrkVolPitSet (pret pokeemerald src/m4a.c, SAT-R sa2
 * src/lib/m4a/m4a.c): recompute a track's stereo volume (flag 0x01) and its
 * key and fine pitch (flag 0x04), then clear both update flags.
 */
void func_08145A98(MusicPlayer *player, MusicPlayerTrack *track)
{
    if (track->flags & 0x01) {
        s32 x;
        s32 y;

        x = (u32)(track->song_volume * track->volume) >> 5;

        if (track->modulation_type == 1)
            x = (u32)(x * (track->modulation + 128)) >> 7;

        y = 2 * track->song_pan + track->pan;

        if (track->modulation_type == 2)
            y += track->modulation;

        if (y < -128)
            y = -128;
        else if (y > 127)
            y = 127;

        track->volume_right = (u32)((y + 128) * x) >> 8;
        track->volume_left = (u32)((127 - y) * x) >> 8;
    }

    if (track->flags & 0x04) {
        s32 bend = track->bend * track->bend_range;
        s32 x = (track->tune + bend) * 4
              + (track->song_key_shift << 8)
              + (track->key_shift << 8)
              + track->pitch;

        if (track->modulation_type == 0)
            x += 16 * track->modulation;

        track->key_calculated = x >> 8;
        track->pitch_calculated = x;
    }

    track->flags &= ~(0x04 | 0x01);
}
