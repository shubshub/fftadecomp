#include "ffta.h"

struct Channel {
    u8 unknown0[2];
    u8 left;
    u8 right;
    u8 unknown4[0xE];
    u8 volume;
    u8 unknown13;
    s8 balance;
};

struct Track {
    u8 unknown[0x10];
    u8 left;
    u8 right;
};

void func_08144DD8(struct Channel *channel, const struct Track *track)
{
    s32 volume = channel->volume;
    s32 balance = channel->balance;
    s32 value;

    value = ((128 + balance) * volume * track->left) >> 14;
    if ((u32)value > 255)
        value = 255;
    channel->left = value;

    value = ((127 - balance) * volume * track->right) >> 14;
    if ((u32)value > 255)
        value = 255;
    channel->right = value;
}
