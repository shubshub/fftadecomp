#include "ffta.h"

typedef struct {
    u8 unknown_00[0x26];
    u8 length;
    u8 unknown_27[0x19];
    const u8 *cursor;
} MusicTrack;

/* Complete target: [0x081465BC, 0x081465CE), 18 bytes.
 * MusicPlayer2000 MP2K_event_xleng, from SAT-R/sa2 src/lib/m4a/m4a.c.
 * Read the command byte into the track's length and advance. */
void func_081465BC(void *player, MusicTrack *track)
{
    track->length = *track->cursor;
    track->cursor++;
}
