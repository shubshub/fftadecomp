#include "ffta.h"

/* Immediate DMA word fill from the local copy of value. */
typedef struct {
    u8 unknown_00[12];
    u8 state;
    u8 unknown_0d[3];
} DmaChannel;

typedef struct {
    const void *source;
    void *destination;
    u32 control;
} DmaRegisters;

extern u16 data_03002BC0[];
extern DmaChannel data_03002BD0[];
extern DmaRegisters *const data_0836D470[];

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

s32 func_08000DBC(u32 value, void *destination, u16 count)
{
    s32 channel = available_channel(&value, destination);

    if (channel >= 0) {
        u32 control = 0x85000000 | count;
        /* plausible: this table points to the DMA channel hardware registers. */
        volatile DmaRegisters *registers = data_0836D470[channel];

        registers->source = &value;
        registers->destination = destination;
        registers->control = control;
    }
    return channel;
}
