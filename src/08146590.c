#include "ffta.h"

typedef struct {
    u8 unknown_00[0x2F];
    u8 release;
    u8 unknown_30[0x10];
    const u8 *cursor;
} MusicTrack;

/* Complete target: [0x08146590, 0x081465A2), 18 bytes.
 * MusicPlayer2000 MP2K_event_xrele, from SAT-R/sa2 src/lib/m4a/m4a.c.
 * Read the command byte into the track's release and advance. */
void func_08146590(void *player, MusicTrack *track)
{
    track->release = *track->cursor;
    track->cursor++;
}
