#include "ffta.h"

typedef struct {
    u8 flags;
    u8 unknown_01[0x16];
    u8 mod_depth;
    u8 unknown_18[0x38];
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

/* Complete [0x08146284, 0x081462F8): 116 bytes, 54 instructions.
 * m4a.c m4aMPlayModDepthSet: set the modulation depth of the selected tracks
 * and clear their modulation when the depth is zero.
 */
void func_08146284(MusicPlayer *player, u16 selected_tracks, u8 mod_depth)
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
                track->mod_depth = mod_depth;
                /* Tests the stored depth: the ROM keeps a copy of it in sb
                 * (0x081462B2) and tests that (0x081462CA). */
                if (!track->mod_depth)
                    func_08146264(track);
            }
        }
        remaining--;
        track++;
        bit <<= 1;
    }
    player->signature = 0x68736D53;
}
