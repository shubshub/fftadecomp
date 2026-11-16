#include "ffta.h"

/*
 * func_08146264 - complete target [0x08146264, 0x08146282), 30 bytes,
 * 15 instructions:
 *   011c 0022 0020 8876 8875 087e 0028 01d1 0c20 00e0 0320 0a78 1043 0870 7047
 *
 * m4a.c ClearModM (pret pokeemerald/pokefirered src/m4a.c, SAT-R sa2
 * src/lib/m4a/m4a.c), built with old_agbcc -O2 like the rest of the m4a unit:
 * the leaf returns through bx lr with no lr save.  It resets the LFO phase
 * (+0x1A) and the current modulation (+0x16), then flags the track for a pitch
 * update (0x0C) when the modulation type (+0x18) is vibrato, or for a volume
 * update (0x03) otherwise.
 */

typedef struct MusicPlayerTrack08146264 {
    u8 flags;
    u8 unknown_01[0x15];
    s8 modulation;
    u8 unknown_17;
    u8 modulation_type;
    u8 unknown_19;
    u8 lfo_phase;
    u8 unknown_1B[0x35];
} MusicPlayerTrack08146264;

void func_08146264(MusicPlayerTrack08146264 *track)
{
    track->lfo_phase = 0;
    track->modulation = 0;

    if (track->modulation_type == 0)
        track->flags |= 0x0C;
    else
        track->flags |= 0x03;
}
