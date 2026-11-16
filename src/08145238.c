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

typedef struct {
    MusicPlayer *player;
    MusicPlayerTrack *tracks;
    u8 track_count;
    u8 unknown_09;
    u16 unknown_0A;
} MusicPlayerEntry;

typedef struct {
    const void *header;
    u16 music_player;
    u16 priority;
} Song;

extern const MusicPlayerEntry g_table_0814BB24[];
extern const Song g_table_0814BB48[];
extern void func_081458AC(void *player, const void *song);
extern void func_08145100(MusicPlayer *player);

/* Complete [0x08145238, 0x0814528C): 84 bytes, 34 instructions.
 * 00b50004094a0a49400b401883885900c9188900891809680b680268934209d0081c111c
 * 00f026fb12e0000024bb140848bb14084a688888002804d1081c191c00f018fb04e0002a
 * 02da081cfff73cff01bc0047
 * m4a.c m4aSongNumStartOrContinue: start song song_id unless its music player
 * already holds it; restart it when no track is active, resume it when paused.
 */
void func_08145238(u16 song_id)
{
    const MusicPlayerEntry *players = g_table_0814BB24;
    const Song *songs = g_table_0814BB48;
    const Song *song = &songs[song_id];
    const MusicPlayerEntry *entry = &players[song->music_player];

    if (entry->player->song != song->header)
        func_081458AC(entry->player, song->header);
    else if ((entry->player->status & 0xFFFF) == 0)
        func_081458AC(entry->player, song->header);
    else if (entry->player->status & 0x80000000)
        func_08145100(entry->player);
}
