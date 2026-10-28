#include "ffta.h"

/* 0x08000D48..0x08000D90: 72 bytes / 31 instructions. */
struct Transfer08000D48 {
    const void *source;
    void *destination;
    u32 control;
    u8 active;
    u8 state;
    u8 unknown_0E[2];
};

extern u16 data_03002BC0[];
extern struct Transfer08000D48 data_03002BD0[];

void func_08000D48(u32 channel, const void *source, void *destination,
                   u32 control)
{
    if (data_03002BC0[channel] == 0) {
        u32 flags = control | 0xA2000000;

        data_03002BD0[channel].source = source;
        data_03002BD0[channel].destination = destination;
        data_03002BD0[channel].control = flags;
        data_03002BD0[channel].active = 1;
        data_03002BD0[channel].state = 0x80;
    }
}
