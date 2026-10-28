#include "ffta.h"

typedef struct {
    u32 unknown_00;
    u32 status;
} MusicPlayer;

extern u8 data_020084D8;
extern MusicPlayer data_0200F2A0;

/* Target: [0x08141838, 0x0814185E), 38 bytes, 14 instructions. */
u8 func_08141838(void)
{
    if (!(data_020084D8 & 1))
        return 0;
    return data_0200F2A0.status >> 31;
}
