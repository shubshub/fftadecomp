#include "ffta.h"

typedef struct MusicPlayerTrack081461FC {
    u8 flags;
    u8 unknown_01[0x14];
    u8 volume;
    u8 unknown_16[0x3A];
} MusicPlayerTrack081461FC;

typedef struct MusicPlayer081461FC {
    void *song;
    u32 status;
    u8 track_count;
    u8 unknown_09[0x23];
    MusicPlayerTrack081461FC *tracks;
    u32 unknown_30;
    u32 signature;
} MusicPlayer081461FC;

/* Complete target [0x081461FC, 0x08146264): 104 bytes, 50 instructions. */
void func_081461FC(MusicPlayer081461FC *player, u16 track_mask, u8 volume)
{
    s32 count;
    MusicPlayerTrack081461FC *track;
    u32 bit;

    if (player->signature != 0x68736D53)
        return;

    player->signature++;
    count = player->track_count;
    track = player->tracks;
    bit = 1;
    while (count > 0) {
        if ((track_mask & bit) && (track->flags & 0x80)) {
            track->volume = volume;
            track->flags |= 3;
        }
        count--;
        track++;
        bit <<= 1;
    }
    player->signature = 0x68736D53;
}
