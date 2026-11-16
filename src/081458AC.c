#include "ffta.h"

/* m4a.c MPlayStart (pret pokeemerald src/m4a.c, SAT-R sa2 src/lib/m4a/m4a.c).
 * Complete [0x081458AC, 0x08145990): 228 bytes, 109 instructions.
 * f0b5474680b4051c0f1c696b3448814261d1e87aba78002813d02868002805d0e96a4020
 * 09780840002805d16968a888002806d0002904dbb878021c687a904249d8686b01306863
 * 002169602f60786828636a72e9609620a88328846a30e8836984a9840026ec6a39788e42
 * 19da287a864226dab046281c211cfff735fac020207041462162b100381c083040180068
 * 2064013650343878864202da297a8e42e9db287a86420cda00218846281c211cfff71afa
 * 4046207001365034297a8e42f4db8020f9780840002802d0f878fff797fe0348686308bc
 * 9846f0bc01bc0047536d7368
 */

typedef struct {
    u8 flags;
    u8 unknown_01[0x1F];
    void *channel;
    u8 unknown_24[0x1C];
    const u8 *cursor;
    u8 unknown_44[0x0C];
} MusicPlayerTrack;

typedef struct {
    u8 track_count;
    u8 unknown_01;
    u8 priority;
    u8 reverb;
    const void *tone;
    const u8 *parts[1];
} SongHeader;

typedef struct {
    const SongHeader *song;
    u32 status;
    u8 track_count;
    u8 priority;
    u8 unknown_0A;
    u8 check_priority;
    u32 clock;
    u8 unknown_10[0x0C];
    u16 base_tempo;
    u16 tempo_scale;
    u16 tempo;
    u16 tempo_counter;
    u16 fade_interval;
    u8 unknown_26[6];
    MusicPlayerTrack *tracks;
    const void *tone;
    u32 signature;
} MusicPlayer;

extern void func_08144D94(MusicPlayer *player, MusicPlayerTrack *track);
extern void func_081456AC(u32 mode);

void func_081458AC(MusicPlayer *player, const SongHeader *song)
{
    s32 i;
    u8 check_priority;
    MusicPlayerTrack *track;

    if (player->signature != 0x68736D53)
        return;

    check_priority = player->check_priority;

    if (!check_priority
        || ((!player->song || !(player->tracks[0].flags & 0x40))
            && ((player->status & 0xFFFF) == 0 || (player->status & 0x80000000)))
        || (player->priority <= song->priority)) {
        /* m4a.c's player lock; the ROM keeps both stores to +0x34
         * (0x081458F2 and 0x08145980). */
        player->signature++;
        player->status = 0;
        player->song = song;
        player->tone = song->tone;
        player->priority = song->priority;
        player->clock = 0;
        player->base_tempo = 150;
        player->tempo = 150;
        player->tempo_scale = 0x100;
        player->tempo_counter = 0;
        player->fade_interval = 0;

        i = 0;
        track = player->tracks;

        while (i < song->track_count && i < player->track_count) {
            func_08144D94(player, track);
            track->flags = 0x80 | 0x40; /* MPT_FLG_EXIST | MPT_FLG_START */
            track->channel = 0;
            track->cursor = song->parts[i];
            i++;
            track++;
        }

        while (i < player->track_count) {
            func_08144D94(player, track);
            track->flags = 0;
            i++;
            track++;
        }

        if (song->reverb & 0x80)
            func_081456AC(song->reverb);

        player->signature = 0x68736D53;
    }
}
