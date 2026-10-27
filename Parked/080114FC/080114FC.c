#include "ffta.h"

/* 0x080114FC..0x08011564: 104 bytes. */
struct Entry080114FC {
    u8 active;
    u8 unknown_01[0x1B];
    u8 channel;
    u8 unknown_1D[0x23];
};

struct State080114FC {
    u16 count;
    u16 unknown_02;
    void *channel2;
    void *channel0;
    void *channel1;
    void *channel3;
    struct Entry080114FC *entries;
};

extern struct State080114FC data_02009170;

void func_080114FC(u8 channel)
{
    int i = 0;
    struct State080114FC *state = &data_02009170;

    for (; i < data_02009170.count; ++i) {
        struct Entry080114FC *entry = &data_02009170.entries[i];

        if (entry->active && entry->channel == channel)
            entry->active = 0;
    }
    switch (channel) {
    case 0:
        state->channel0 = 0;
        break;
    case 1:
        state->channel1 = 0;
        break;
    case 2:
        state->channel2 = 0;
        break;
    case 3:
        state->channel3 = 0;
        break;
    }
}
