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

/* Complete [0x08145100, 0x0814511C): 28 bytes, 10 instructions.
 * Target: 021c536b0348834203d150680249084050607047536d7368ffffff7f.
 * m4a.c MPlayContinue: clears the pause bit of a player whose signature is set.
 */
void func_08145100(MusicPlayer *player)
{
    if (player->signature == 0x68736D53) {
        /* m4a.c's player lock, as in 08145990 and 081461FC. Neither lock
         * store is in the ROM; the signature compared at 0x08145106 is held
         * in r3, clear of the r0/r1 status update at 0x0814510A..0x08145110. */
        player->signature++;
        player->status &= ~0x80000000;
        player->signature = 0x68736D53;
    }
}
