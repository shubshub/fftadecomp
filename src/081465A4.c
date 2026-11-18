#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1E];
    u8 echo_volume;
    u8 unknown_1F[0x21];
    const u8 *cursor;
} MusicTrack;

/* Complete target: [0x081465A4, 0x081465B0), 12 bytes.
 * MusicPlayer2000 MP2K_event_xiecv, from SAT-R/sa2 src/lib/m4a/m4a.c.
 * Read the command byte into the track's echo volume and advance. */
void func_081465A4(void *player, MusicTrack *track)
{
    track->echo_volume = *track->cursor;
    track->cursor++;
}
