#include "ffta.h"

typedef struct SongHeader SongHeader;

typedef struct {
    const SongHeader *song;
    u32 status;
} MusicPlayer;

typedef struct {
    MusicPlayer *player;
    u32 unknown_04;
    u32 unknown_08;
} MusicPlayerEntry;

typedef struct {
    const SongHeader *song;
    u16 player_index;
    u16 unknown_06;
} SongEntry;

extern const MusicPlayerEntry g_table_0814BB24[];
extern const SongEntry g_table_0814BB48[];
extern void func_081458AC(MusicPlayer *player, const SongHeader *song);
extern void func_08145100(MusicPlayer *player);

/* Complete [0x08145238, 0x0814528C): 84 bytes, 34 instructions. */
void func_08145238(u16 song_number)
{
    MusicPlayer *player;
    const MusicPlayerEntry *players = g_table_0814BB24;
    const SongEntry *songs = g_table_0814BB48;
    const SongEntry *entry = &songs[song_number];

    player = players[entry->player_index].player;

    if (player->song != entry->song) {
        func_081458AC(player, entry->song);
    } else if ((player->status & 0xFFFF) == 0) {
        func_081458AC(player, player->song);
    } else if (player->status & 0x80000000) {
        func_08145100(player);
    }
}
