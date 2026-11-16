#include "ffta.h"

/* Complete [0x08145BF4, 0x08145C44): 80 bytes, 30 instructions plus literal pools.
 * m4a CgbOscOff: silence one CGB sound channel through its envelope and
 * frequency-control registers. */
void func_08145BF4(u8 channel)
{
    switch (channel) {
    case 1:
        /* plausible: mapped SOUND1CNT_H envelope byte (NR12) is a physical register. */
        *(volatile u8 *)0x04000063 = 8;
        /* plausible: mapped SOUND1CNT_X control byte (NR14) is a physical register. */
        *(volatile u8 *)0x04000065 = 0x80;
        break;
    case 2:
        /* plausible: mapped SOUND2CNT_L envelope byte (NR22) is a physical register. */
        *(volatile u8 *)0x04000069 = 8;
        /* plausible: mapped SOUND2CNT_H control byte (NR24) is a physical register. */
        *(volatile u8 *)0x0400006D = 0x80;
        break;
    case 3:
        /* plausible: mapped SOUND3CNT_L enable byte (NR30) is a physical register. */
        *(volatile u8 *)0x04000070 = 0;
        break;
    default:
        /* plausible: mapped SOUND4CNT_L envelope byte (NR42) is a physical register. */
        *(volatile u8 *)0x04000079 = 8;
        /* plausible: mapped SOUND4CNT_H control byte (NR44) is a physical register. */
        *(volatile u8 *)0x0400007D = 0x80;
    }
}
