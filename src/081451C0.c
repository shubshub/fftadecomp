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

/* Complete [0x081451C0, 0x081451EC): 44 bytes, 17 instructions.
 * 00b50004074a0849400b401883885900c918890089180a680168101c00f066fb01bc0047
 * 24bb140848bb1408
 * m4a.c m4aSongNumStart: start song song_id on the music player its song
 * table entry names.
 */
void func_081451C0(u16 song_id)
{
    const MusicPlayerEntry *players = g_table_0814BB24;
    const Song *songs = g_table_0814BB48;
    const Song *song = &songs[song_id];
    const MusicPlayerEntry *entry = &players[song->music_player];

    func_081458AC(entry->player, song->header);
}
