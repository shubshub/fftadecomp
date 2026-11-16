#include "ffta.h"

/* m4a.c FadeOutBody (pret pokeemerald src/m4a.c, SAT-R sa2 src/lib/m4a/m4a.c).
 * Complete [0x081459D0, 0x08145A98): 200 bytes, 96 instructions plus a
 * literal pool.
 * f0b5061cb18c00295bd0f08c0138f0840b4b1a1c0004030c002b52d1f184318d0220084000
 * 280dd0081c103030851040ff2830d9802040003085b3842be00000ffff0000081c10383085
 * 10400004002821dc357af46a002d0ddd301c211cfff7b1f90120378d3840002800d1207001
 * 3d5034002df1dc0120318d0840002804d0706880210906084301e08020000670600020b084
 * 15e0357af46a002d11dd8023002703222178181c0840002805d0378db808e074081c104320
 * 70013d5034002df0dcf0bc01bc0047
 */

/* m4a_internal.h fade bits; MUSICPLAYER_STATUS_PAUSE is 0x80000000,
 * MPT_FLG_EXIST 0x80 and MPT_FLG_VOLCHG 3. */
#define TEMPORARY_FADE 0x0001
#define FADE_IN 0x0002
#define FADE_VOL_SHIFT 2

typedef struct {
    u8 flags;
    u8 unknown_01[0x12];
    u8 volume;
    u8 unknown_14[0x3C];
} MusicPlayerTrack;

typedef struct {
    void *song;
    u32 status;
    u8 track_count;
    u8 unknown_09[0x1B];
    u16 fade_interval;
    u16 fade_counter;
    u16 fade_volume;
    u8 unknown_2A[2];
    MusicPlayerTrack *tracks;
    u32 unknown_30;
    u32 signature;
} MusicPlayer;

extern void func_08144D94(MusicPlayer *player, MusicPlayerTrack *track);

void func_081459D0(MusicPlayer *player)
{
    s32 i;
    MusicPlayerTrack *track;
    u16 fade_volume;

    if (player->fade_interval == 0)
        return;
    if (--player->fade_counter != 0)
        return;

    player->fade_counter = player->fade_interval;

    if (player->fade_volume & FADE_IN) {
        if ((u16)(player->fade_volume += (4 << FADE_VOL_SHIFT)) >= (64 << FADE_VOL_SHIFT)) {
            player->fade_volume = (64 << FADE_VOL_SHIFT);
            player->fade_interval = 0;
        }
    } else {
        if ((s16)(player->fade_volume -= (4 << FADE_VOL_SHIFT)) <= 0) {
            i = player->track_count;
            track = player->tracks;

            while (i > 0) {
                u32 val;

                func_08144D94(player, track);

                val = TEMPORARY_FADE;
                fade_volume = player->fade_volume;
                val &= fade_volume;

                if (!val)
                    track->flags = 0;

                i--;
                track++;
            }

            if (player->fade_volume & TEMPORARY_FADE)
                player->status |= 0x80000000;
            else
                player->status = 0x80000000;

            player->fade_interval = 0;
            return;
        }
    }

    i = player->track_count;
    track = player->tracks;

    while (i > 0) {
        if (track->flags & 0x80) {
            fade_volume = player->fade_volume;

            track->volume = (fade_volume >> FADE_VOL_SHIFT);
            track->flags |= 3;
        }

        i--;
        track++;
    }
}
