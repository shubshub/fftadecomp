#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1F];
    u8 echo_length;
    u8 unknown_20[0x20];
    const u8 *cursor;
} MusicTrack;

/* Complete target: [0x081465B0, 0x081465BC), 12 bytes.
 * MusicPlayer2000 MP2K_event_xiecl, from SAT-R/sa2 src/lib/m4a/m4a.c.
 * Read the command byte into the track's echo length and advance. */
void func_081465B0(void *player, MusicTrack *track)
{
    track->echo_length = *track->cursor;
    track->cursor++;
}
