#include "ffta.h"

/* Target: complete [0x08000D90, 0x08000DBC), 44 bytes. */
typedef struct {
    const void *source;
    void *destination;
    u32 control;
    u8 state;
    u8 flags;
    u16 unknown_0E;
} DmaRequest08000D90;

extern DmaRequest08000D90 data_03002BD0[4];
extern DmaRequest08000D90 data_03002C10[4];

void func_08000D90(u32 channel)
{
    if (data_03002C10[channel].state != 0)
    {
        data_03002BD0[channel].state = 2;
        data_03002BD0[channel].flags |= 0x80;
    }
}
