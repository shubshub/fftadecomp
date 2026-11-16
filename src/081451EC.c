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

/* Complete [0x081451EC, 0x08145238): 76 bytes, 31 instructions.
 * 00b50004094a0a49400b401883885900c9188900891809680b680268934209d0081c111c
 * 00f04cfb0ee0000024bb140848bb14084a688888002801d0002a03da081c191c00f03cfb
 * 01bc0047
 * m4a.c m4aSongNumStartOrChange: start song song_id unless its music player
 * already plays it; restart it when the player has no active track or is
 * paused.
 */
void func_081451EC(u16 song_id)
{
    const MusicPlayerEntry *players = g_table_0814BB24;
    const Song *songs = g_table_0814BB48;
    const Song *song = &songs[song_id];
    const MusicPlayerEntry *entry = &players[song->music_player];

    if (entry->player->song != song->header) {
        func_081458AC(entry->player, song->header);
    } else {
        if ((entry->player->status & 0xFFFF) == 0
         || (entry->player->status & 0x80000000))
            func_081458AC(entry->player, song->header);
    }
}
