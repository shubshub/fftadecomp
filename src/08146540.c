#include "ffta.h"

typedef struct {
    u8 unknown_00[0x24];
    u8 tone_type;
    u8 unknown_25[0x1B];
    const u8 *cursor;
} MusicTrack;

/* Complete target: [0x08146540, 0x08146552), 18 bytes.
 * MusicPlayer2000 MP2K_event_xtype, from SAT-R/sa2 src/lib/m4a/m4a.c.
 * Read the command byte into the track's tone type and advance. */
void func_08146540(void *player, MusicTrack *track)
{
    track->tone_type = *track->cursor;
    track->cursor++;
}
