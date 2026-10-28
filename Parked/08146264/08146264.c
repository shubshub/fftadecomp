#include "ffta.h"

typedef struct {
    u8 flags;
    u8 unknown_01[0x15];
    u8 modulation;
    u8 unknown_17;
    u8 mode;
    u8 unknown_19;
    u8 phase;
} ModulationTrack;

u8 func_08146264(ModulationTrack *track)
{
    u8 mask;

    track->modulation = track->phase = 0;
    if (track->mode == 0)
        mask = 0x0C;
    else
        mask = 0x03;
    return track->flags |= mask;
}
