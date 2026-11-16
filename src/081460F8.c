#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1C];
    u16 base_tempo;
    u16 tempo_scale;
    u16 tempo;
    u8 unknown_22[0x12];
    u32 signature;
} MusicPlayer;

/* Complete [0x081460F8, 0x08146120): 40 bytes, 17 instructions.
 * 10b5021c0904090c536b0648834205d1d183948b081c60430012108410bc01bc00470000
 * 536d7368
 * m4a.c m4aMPlayTempoControl: set a player's tempo scale and recompute its
 * tempo from the base tempo.
 */
void func_081460F8(MusicPlayer *player, u16 tempo_scale)
{
    if (player->signature == 0x68736D53) {
        /* The m4a signature lock, as in src/08145990.c and src/08146120.c and
         * in the public m4aMPlayTempoControl text.  Neither lock store is in
         * the ROM; the signature loaded at 0x08146100 stays in r3, clear of
         * the body, which uses r4 (push {r4, lr} at 0x081460F8). */
        player->signature++;
        player->tempo_scale = tempo_scale;
        player->tempo = (player->base_tempo * player->tempo_scale) >> 8;
        player->signature = 0x68736D53;
    }
}
