#include "ffta.h"

/* 0x08000EC8 .. 0x08000F48: 128 bytes. */
typedef struct {
    u8 unknown_00[12];
    u8 state;
    u8 unknown_0d[3];
} DmaChannel08000EC8;

typedef struct {
    const void *source;
    void *destination;
    u32 control;
} DmaRegisters08000EC8;

extern u16 data_03002BC0[];
extern DmaChannel08000EC8 data_03002BD0[];
extern DmaRegisters08000EC8 *const data_0836D470[];

static inline s32 available_channel(const void *source, void *destination)
{
    s32 channel;

    if ((u32)destination >= 0x08000000) {
        channel = 3;
    } else {
        channel = 0;
        if ((u32)source >= 0x08000000)
            channel = 1;
    }

    for (; channel < 4; channel++) {
        if (!data_03002BC0[channel] &&
            (data_03002BD0[channel].state == 0 ||
             data_03002BD0[channel].state == 2))
            return channel;
    }
    return -1;
}

s32 func_08000EC8(const void *source, void *destination, u16 count)
{
    s32 channel = available_channel(source, destination);

    if (channel >= 0) {
        u32 control = 0x84000000 | count;
        DmaRegisters08000EC8 *registers = data_0836D470[channel];

        registers->source = source;
        registers->destination = destination;
        registers->control = control;
    }
    return channel;
}
