#include "ffta.h"

typedef struct {
    u8 unknown_00[0x2C];
    u8 attack;
    u8 unknown_2D[0x13];
    const u8 *cursor;
} MusicTrack;

/* Complete target: [0x08146554, 0x08146566), 18 bytes.
 * MusicPlayer2000 MP2K_event_xatta, from SAT-R/sa2 src/lib/m4a/m4a.c.
 * Read the command byte into the track's attack and advance. */
void func_08146554(void *player, MusicTrack *track)
{
    track->attack = *track->cursor;
    track->cursor++;
}
