#include "ffta.h"

typedef struct MusicPlayer MusicPlayer;
extern void func_08145100(MusicPlayer *player);

/* Complete target: [0x08145320, 0x0814532A), 10 bytes.
 * MusicPlayer2000 m4aMPlayContinue, from SAT-R/sa2 src/lib/m4a/m4a.c. */
void func_08145320(MusicPlayer *player)
{
    func_08145100(player);
}
