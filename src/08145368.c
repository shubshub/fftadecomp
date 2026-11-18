#include "ffta.h"

typedef struct {
    u8 unknown_00[0x24];
    u16 fade_interval;
    u16 fade_counter;
    u16 fade_volume;
    u8 unknown_2A[0x0A];
    u32 signature;
} MusicPlayer;

/* Complete target: [0x08145368, 0x08145388), 32 bytes.
 * MusicPlayer2000 m4aMPlayFadeOutTemporarily, from SAT-R/sa2
 * src/lib/m4a/m4a.c. Start a temporary fade with volume 64 and flag 1. */
void func_08145368(MusicPlayer *player, u16 speed)
{
    if (player->signature == 0x68736D53) {
        player->signature++;
        player->fade_counter = speed;
        player->fade_interval = speed;
        player->fade_volume = (64 << 2) | 1;
        player->signature = 0x68736D53;
    }
}
