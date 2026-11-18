#include "ffta.h"

typedef struct {
    u8 unknown_00[0x2E];
    u8 sustain;
    u8 unknown_2F[0x11];
    const u8 *cursor;
} MusicTrack;

/* Complete target: [0x0814657C, 0x0814658E), 18 bytes.
 * MusicPlayer2000 MP2K_event_xsust, from SAT-R/sa2 src/lib/m4a/m4a.c.
 * Read the command byte into the track's sustain and advance. */
void func_0814657C(void *player, MusicTrack *track)
{
    track->sustain = *track->cursor;
    track->cursor++;
}
