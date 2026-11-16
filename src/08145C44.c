#include "ffta.h"

typedef struct {
    u8 unknown_00[2];
    u8 right_volume;
    u8 left_volume;
    u8 unknown_04[2];
    u8 sustain;
    u8 unknown_07[3];
    u8 envelope_goal;
    u8 unknown_0B[0x0E];
    u8 sustain_goal;
    u8 unknown_1A;
    u8 pan;
    u8 pan_mask;
} CgbChannel;

/* m4a.c CgbPan, a static inline in the public MusicPlayer2000 text (pret
 * pokeemerald src/m4a.c, SAT-R sa2 src/lib/m4a/m4a.c): hard-pan a CGB channel
 * to the louder side when that side is at least twice the other. */
static inline int CgbPan(CgbChannel *chan)
{
    u32 right_volume = chan->right_volume;
    u32 left_volume = chan->left_volume;

    /* The library's re-narrowing: the ROM zero-extends each loaded byte again
     * (ldrb; lsls #24; lsrs #24 at 0x08145C48-0x08145C52) and halves the
     * shifted copy (lsrs #25 at 0x08145C58, 0x08145C64). */
    if ((right_volume = (u8)right_volume) >= (left_volume = (u8)left_volume)) {
        if (right_volume / 2 >= left_volume) {
            chan->pan = 0x0F;
            return 1;
        }
    } else {
        if (left_volume / 2 >= right_volume) {
            chan->pan = 0xF0;
            return 1;
        }
    }

    return 0;
}

/* Complete [0x08145C44, 0x08145CAC): 104 bytes, 52 instructions.
 * m4a.c CgbModVol (sa2 text; this revision has no gSoundInfo.mode test).
 * The ROM computes envelope_goal separately in each arm (0x08145C74,
 * 0x08145C7E). */
void func_08145C44(CgbChannel *chan)
{
    if (!CgbPan(chan)) {
        chan->pan = 0xFF;
        chan->envelope_goal = (u32)(chan->right_volume + chan->left_volume) / 16;
    } else {
        chan->envelope_goal = (u32)(chan->right_volume + chan->left_volume) / 16;

        if (chan->envelope_goal > 15)
            chan->envelope_goal = 15;
    }

    chan->sustain_goal = (chan->envelope_goal * chan->sustain + 15) >> 4;
    chan->pan &= chan->pan_mask;
}
