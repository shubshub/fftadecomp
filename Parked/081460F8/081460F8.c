#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1C];
    u16 base_tempo;
    u16 tempo_scale;
    u16 tempo;
    u8 unknown_22[0x12];
    u32 signature;
} MusicPlayer081460F8;

/* Complete [0x081460F8, 0x08146120): 40 bytes, 17 instructions. */
void func_081460F8(MusicPlayer081460F8 *player, u16 scale)
{
    if (player->signature != 0x68736D53)
        return;

    player->tempo_scale = scale;
    player->tempo = (scale * player->base_tempo) >> 8;
}
