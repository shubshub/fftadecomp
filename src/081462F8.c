#include "ffta.h"

typedef struct {
    u8 flags;
    u8 unknown_01[0x18];
    u8 lfo_speed;
    u8 unknown_1A[0x36];
} PlayerTrack;

typedef struct {
    u8 unknown_00[8];
    u8 track_count;
    u8 unknown_09[0x23];
    PlayerTrack *tracks;
    u32 unknown_30;
    u32 signature;
} MusicPlayer;

extern void func_08146264(PlayerTrack *track);

/* Complete [0x081462F8, 0x0814636C): 116 bytes, 54 instructions.
 * m4a.c m4aMPlayLFOSpeedSet: set the LFO speed of the selected tracks and
 * clear their modulation when the speed is zero.
 */
void func_081462F8(MusicPlayer *player, u16 selected_tracks, u8 lfo_speed)
{
    s32 remaining;
    u32 bit;
    PlayerTrack *track;

    if (player->signature != 0x68736D53)
        return;

    player->signature++;
    remaining = player->track_count;
    track = player->tracks;
    bit = 1;
    while (remaining > 0) {
        if (selected_tracks & bit) {
            if (track->flags & 0x80) {
                track->lfo_speed = lfo_speed;
                /* Tests the stored speed: the ROM keeps a copy of it in sb
                 * (0x08146326) and tests that (0x0814633E). */
                if (!track->lfo_speed)
                    func_08146264(track);
            }
        }
        remaining--;
        track++;
        bit <<= 1;
    }
    player->signature = 0x68736D53;
}
