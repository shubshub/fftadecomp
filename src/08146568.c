#include "ffta.h"

typedef struct {
    u8 unknown_00[0x2D];
    u8 decay;
    u8 unknown_2E[0x12];
    const u8 *cursor;
} MusicTrack;

/* Complete target: [0x08146568, 0x0814657A), 18 bytes.
 * MusicPlayer2000 MP2K_event_xdeca, from SAT-R/sa2 src/lib/m4a/m4a.c.
 * Read the command byte into the track's decay and advance. */
void func_08146568(void *player, MusicTrack *track)
{
    track->decay = *track->cursor;
    track->cursor++;
}
