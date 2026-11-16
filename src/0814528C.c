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
extern void func_08145990(MusicPlayer *player);

/* Complete [0x0814528C, 0x081452C0): 52 bytes, 20 instructions.
 * 00b50004094a0a49400b401883885900c918890089180a6811680068814202d1101c00f0
 * 6ffb01bc0047000024bb140848bb1408
 * m4a.c m4aSongNumStop: stop song song_id's music player if it holds that song.
 */
void func_0814528C(u16 song_id)
{
    const MusicPlayerEntry *players = g_table_0814BB24;
    const Song *songs = g_table_0814BB48;
    const Song *song = &songs[song_id];
    const MusicPlayerEntry *entry = &players[song->music_player];

    if (entry->player->song == song->header)
        func_08145990(entry->player);
}
