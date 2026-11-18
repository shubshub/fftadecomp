#include "ffta.h"

typedef struct {
    u8 unknown_00[0x27];
    u8 pan_sweep;
    u8 unknown_28[0x18];
    const u8 *cursor;
} MusicTrack;

/* Complete target: [0x081465D0, 0x081465E2), 18 bytes.
 * MusicPlayer2000 MP2K_event_xswee, from SAT-R/sa2 src/lib/m4a/m4a.c.
 * Read the command byte into the tone's pan/sweep register and advance. */
void func_081465D0(void *player, MusicTrack *track)
{
    track->pan_sweep = *track->cursor;
    track->cursor++;
}
