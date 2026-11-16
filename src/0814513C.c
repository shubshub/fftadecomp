#include "ffta.h"

typedef struct MusicPlayerTrack MusicPlayerTrack;

typedef struct {
    void *song;
    u32 status;
    u8 track_count;
    u8 unknown_09[2];
    u8 unknown_0B;
    u8 unknown_0C[0x0C];
    u8 *unknown_18;
    u8 unknown_1C[0x10];
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
 * the pool word at 0x081451A8 and narrows it to u16 at 0x08145162. */
extern char g_num_music_players_00000003[];
#define NUM_MUSIC_PLAYERS ((u16)g_num_music_players_00000003)

extern void func_08144594(void);
extern u8 data_030034DC[];
extern u8 data_020084E0[];
extern u8 data_02008EF0[];
extern u8 data_0200F360;
extern const MusicPlayerEntry g_table_0814BB24[];

extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_0814553C(void *state);
extern void func_081453F8(void *channels);
extern void func_081456AC(u32 mode);
extern void func_08145834(MusicPlayer *player, MusicPlayerTrack *tracks, u8 count);

/* Complete [0x0814513C, 0x081451B4): 120 bytes, 37 instructions.
 * Target: 70b514480221494208401349134afcf78ffb134800f0f4f9124800f04ff91248
 *         00f0a6fa11480004000c00280fd0104d061c2c6869682a7a201c00f05dfb6889
 *         e0720c48a0610c35013e002ef1d170bc01bc004795451408dc340003e0000004
 *         e0840002f08e000200f895000300000024bb140860f30002
 * m4a.c m4aSoundInit.
 *
 * The first pool word is 0x08144595, the Thumb address of the routine at
 * 0x08144594; the code clears bit 0 at run time and copies 0xE0 words from
 * there to 0x030034DC with func_0814186C.  func_08144510 branches to that
 * copy through its pool word 0x030034DD.
 */
void func_0814513C(void)
{
    s32 i;

    func_0814186C((const void *)((s32)func_08144594 & ~1), data_030034DC,
        0x040000E0);
    func_0814553C(data_020084E0);
    func_081453F8(data_02008EF0);
    func_081456AC(0x0095F800);
    for (i = 0; i < NUM_MUSIC_PLAYERS; i++) {
        MusicPlayer *player = g_table_0814BB24[i].player;

        func_08145834(player, g_table_0814BB24[i].tracks,
            g_table_0814BB24[i].track_count);
        player->unknown_0B = g_table_0814BB24[i].unknown_0A;
        player->unknown_18 = &data_0200F360;
    }
}
