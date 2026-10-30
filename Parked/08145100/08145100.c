#include "ffta.h"

typedef struct MusicPlayerTrack MusicPlayerTrack;

typedef struct {
    void *song;
    u32 status;
    u8 track_count;
    u8 unknown_09[0x23];
    MusicPlayerTrack *tracks;
    u32 unknown_30;
    u32 signature;
} MusicPlayer;

/* 0x08145100..0x0814511C: 28 complete bytes.
 * Target: 021c536b0348834203d150680249084050607047536d7368ffffff7f.
 */
void func_08145100(MusicPlayer *player)
{
    if (player->signature != 0x68736D53)
        return;

    player->status &= 0x7FFFFFFF;
}
