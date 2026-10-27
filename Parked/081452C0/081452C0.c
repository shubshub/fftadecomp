#include "ffta.h"

typedef struct {
    const void *header;
} MusicPlayer;

typedef struct {
    MusicPlayer *player;
    u8 unknown_04[8];
} MusicPlayerEntry;

typedef struct {
    const void *header;
    u16 player;
    u16 priority;
} Song;

extern const MusicPlayerEntry g_table_0814BB24[];
extern const Song g_table_0814BB48[];
extern void func_08145100(MusicPlayer *player);

/* Target: [0x081452C0, 0x081452F4), 52 bytes, 20 instructions. */
void func_081452C0(u16 song_id)
{
    const MusicPlayerEntry *players = g_table_0814BB24;
    const Song *songs = g_table_0814BB48;
    const Song *song = &songs[song_id];
    MusicPlayer *player = (players + song->player)->player;

    if (player->header == song->header)
        func_08145100(player);
}
