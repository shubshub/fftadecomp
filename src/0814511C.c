#include "ffta.h"

/* m4a.c MPlayFadeOut (pret pokeemerald src/m4a.c, SAT-R sa2 src/lib/m4a/m4a.c).
 * Complete [0x0814511C, 0x0814513C): 32 bytes, 13 instructions.
 * 021c0904090c536b0448834204d1d184918480204000108570470000536d7368
 */

#define FADE_VOL_SHIFT 2

typedef struct {
    u8 unknown_00[0x24];
    u16 fade_interval;
    u16 fade_counter;
    u16 fade_volume;
    u8 unknown_2A[0x0A];
    u32 signature;
} MusicPlayer;

void func_0814511C(MusicPlayer *player, u16 speed)
{
    if (player->signature == 0x68736D53) {
        /* m4a.c's signature lock, as in pret's MPlayFadeOut.  Nothing reads
         * the signature between its two stores, and neither store is in the
         * ROM here, as in MPlayContinue (0x08145100) and m4aMPlayFadeIn
         * (0x08145388); m4aMPlayStop, with a call inside, keeps both (str at
         * 0x0814599E and 0x081459C4, src/08145990.c). */
        player->signature++;
        player->fade_counter = speed;
        player->fade_interval = speed;
        player->fade_volume = 64 << FADE_VOL_SHIFT;
        player->signature = 0x68736D53;
    }
}
