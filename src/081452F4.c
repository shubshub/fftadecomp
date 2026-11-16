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

/* The number of music players, 3: a link-time absolute symbol whose
 * address is the count, pret's gNumMusicPlayers.  The ROM loads it from
 * the pool word at 0x08145318 and narrows it to u16 at 0x081452F8. */
extern char g_num_music_players_00000003[];
#define NUM_MUSIC_PLAYERS ((u16)g_num_music_players_00000003)

extern const MusicPlayerEntry g_table_0814BB24[];
extern void func_08145990(MusicPlayer *player);

/* Complete [0x081452F4, 0x08145320): 44 bytes, 17 instructions.
 * Target: 30b508480004000c002808d0064d041c286800f043fb0c35013c002cf8d130bc
 *         01bc00470300000024bb1408
 * m4a.c m4aMPlayAllStop: stops the player of every entry of g_table_0814BB24.
 */
void func_081452F4(void)
{
    s32 i;

    for (i = 0; i < NUM_MUSIC_PLAYERS; i++)
        func_08145990(g_table_0814BB24[i].player);
}
