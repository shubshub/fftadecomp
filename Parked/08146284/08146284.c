#include "ffta.h"

typedef struct {
    u8 flags;
    u8 unknown_01[0x16];
    u8 modulation;
    u8 unknown_18[0x38];
} PlayerTrack08146284;

typedef struct {
    u8 unknown_00[8];
    u8 track_count;
    u8 unknown_09[0x23];
    PlayerTrack08146284 *tracks;
    u32 unknown_30;
    u32 signature;
} MusicPlayer08146284;

extern void func_08146264(PlayerTrack08146284 *track);

/* Target: complete [0x08146284, 0x081462F8), 116 bytes, 54 instructions. */
void func_08146284(MusicPlayer08146284 *player, u16 selected_tracks, u8 modulation)
{
    PlayerTrack08146284 *track;
    s32 remaining;
    u32 bit;

    if (player->signature == 0x68736d53) {
        player->signature++;
        remaining = player->track_count;
        track = player->tracks;
        bit = 1;
        for (; remaining > 0; remaining--, track++, bit <<= 1) {
            if (!(selected_tracks & bit))
                continue;
            if (!(track->flags & 0x80))
                continue;
            track->modulation = modulation;
            if (track->modulation == 0)
                func_08146264(track);
        }
        player->signature = 0x68736d53;
    }
}
