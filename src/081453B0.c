#include "ffta.h"

typedef struct {
    u8 flags;
    u8 unknown_01[0x0E];
    u8 bend_range;
    u8 unknown_10[3];
    u8 volume;
    u8 unknown_14[5];
    u8 lfo_speed;
    u8 unknown_1a[0x0A];
    u8 tone_type;
    u8 unknown_25[0x2B];
} MusicPlayerTrack;

typedef struct {
    void *song;
    u32 status;
    u8 track_count;
    u8 unknown_09[0x23];
    MusicPlayerTrack *tracks;
    u32 unknown_30;
    u32 signature;
} MusicPlayer;

extern void func_08145528(void *object);

/* Complete [0x081453B0, 0x081453F8): 72 bytes, 35 instructions.
 * f0b5057ac46a002d1bdd80272178381c0840002811d04026301c084000280cd0201c00f0
 * a9f827700220e073e67416206076211c243101200870013d5034002de4dcf0bc01bc0047
 */
void func_081453B0(MusicPlayer *player)
{
    s32 count = player->track_count;
    MusicPlayerTrack *track = player->tracks;

    while (count > 0) {
        if (track->flags & 0x80) {
            if (track->flags & 0x40) {
                func_08145528(track);
                track->flags = 0x80;
                track->bend_range = 2;
                track->volume = 0x40;
                track->lfo_speed = 0x16;
                track->tone_type = 1;
            }
        }
        count--;
        track++;
    }
}
