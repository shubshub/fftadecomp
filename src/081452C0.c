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
extern void func_08145100(MusicPlayer *player);

/* Complete [0x081452C0, 0x081452F4): 52 bytes, 20 instructions.
 * 00b50004094a0a49400b401883885900c918890089180a6811680068814202d1101cfff7
 * 0dff01bc0047000024bb140848bb1408
 * m4a.c m4aSongNumContinue: resume song song_id's music player if it holds
 * that song.
 */
void func_081452C0(u16 song_id)
{
    const MusicPlayerEntry *players = g_table_0814BB24;
    const Song *songs = g_table_0814BB48;
    const Song *song = &songs[song_id];
    const MusicPlayerEntry *entry = &players[song->music_player];

    if (entry->player->song == song->header)
        func_08145100(entry->player);
}
