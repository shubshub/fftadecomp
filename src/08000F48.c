#include "ffta.h"

/* 0x08000F48 .. 0x08000FC8: 128 bytes. */
typedef struct {
    u8 unknown_00[12];
    u8 state;
    u8 unknown_0d[3];
} TransferState;

typedef struct {
    const void *source;
    void *destination;
    u32 control;
} TransferCommand;

extern u16 data_03002BC0[];
extern TransferState data_03002BD0[];
extern TransferCommand *const data_0836D470[];

static inline s32 find_available_channel(const void *source, void *destination)
{
    s32 channel;
    if ((u32)destination > 0x07ffffff)
        channel = 3;
    else {
        channel = 0;
        if ((u32)source > 0x07ffffff)
            channel = 1;
    }
    for (; channel <= 3; ++channel) {
        if (data_03002BC0[channel] == 0 &&
            (data_03002BD0[channel].state == 0 ||
             data_03002BD0[channel].state == 2))
            return channel;
    }
    return -1;
}

s32 func_08000F48(const void *source, void *destination, u16 count)
{
    s32 channel = find_available_channel(source, destination);
    if (channel >= 0) {
        u32 control = count | 0x80000000;
        TransferCommand *command = data_0836D470[channel];
        command->source = source;
        command->destination = destination;
        command->control = control;
    }
    return channel;
}
