#include "ffta.h"

typedef struct MusicPlayer MusicPlayer;
typedef struct MusicTrack MusicTrack;
typedef void (*CommandHandler)(MusicPlayer *, MusicTrack *);
extern CommandHandler data_02008E60[];

/* Complete target: [0x081464E4, 0x081464F8), 20 bytes.
 * MusicPlayer2000 MP2K_event_xxx, from SAT-R/sa2 src/lib/m4a/m4a.c.
 * Dispatch the extension command through jump-table entry zero. */
void func_081464E4(MusicPlayer *player, MusicTrack *track)
{
    CommandHandler handler = data_02008E60[0];

    handler(player, track);
}
