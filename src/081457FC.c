#include "ffta.h"

/* MusicPlayer2000 m4aSoundVSyncOn. The FFTA mono build uses DMA1. */
typedef struct {
    u32 lockStatus;
    volatile u8 dmaCounter;
} SoundMixerState;

extern SoundMixerState *data_03007FF0;

void func_081457FC(void)
{
    SoundMixerState *soundInfo = data_03007FF0;
    u32 lockStatus = soundInfo->lockStatus;

    if (lockStatus == 0x68736D53)
        return;

    /* plausible: DMA1CNT_H enables repeating 32-bit FIFO transfers. */
    *(volatile u16 *)0x040000C6 = 0xB600;
    soundInfo->dmaCounter = 0;
    soundInfo->lockStatus = lockStatus - 10;
}
