#include "ffta.h"

typedef struct {
    void *song;
    u32 status;
    u8 unknown_08[0x1C];
    u16 fade_interval;
    u16 fade_counter;
    u16 fade_volume;
    u8 unknown_2A[0x0A];
    u32 signature;
} MusicPlayer;

/* Complete [0x08145388, 0x081453B0): 40 bytes, 16 instructions.
 * 021c0904090c536b0548834207d1d18491840220108550680249084050607047536d7368ffffff7f
 */
void func_08145388(MusicPlayer *player, u16 speed)
{
    if (player->signature == 0x68736D53) {
        /* The m4a signature lock, as in src/08145990.c and src/08146120.c and in
         * the public m4aMPlayFadeIn text. The signature is known to be 0x68736D53
         * here and the ROM keeps no store to +0x34; it loads it into r3 at
         * 0x0814538E and keeps speed in r1. */
        player->signature++;
        player->fade_counter = speed;
        player->fade_interval = speed;
        player->fade_volume = 2; /* fade in, starting from volume 0 */
        player->status &= ~0x80000000;
        player->signature = 0x68736D53;
    }
}
