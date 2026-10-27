#include "ffta.h"

struct DmaRequest080009AC {
    const void *source;
    void *destination;
    u32 control;
    u8 state;
    u8 flags;
    u16 unknown_0E;
};

extern u16 data_03002BC0[4];
extern struct DmaRequest080009AC data_03002BD0[4];

static inline s32 find_dma_slot(const void *source, void *destination)
{
    u32 address_limit = 0x07FFFFFF;
    s32 i = 3;

    if ((u32)destination <= address_limit) {
        i = 0;
        if ((u32)source > address_limit)
            i = 1;
    }
    for (; i < 4; i++) {
        if (data_03002BC0[i] == 0 &&
            (data_03002BD0[i].state == 0 || data_03002BD0[i].state == 2))
            return i;
    }
    return -1;
}

/* Complete [0x080009AC, 0x08000A48): 156 bytes, 67 instructions. */
s32 func_080009AC(const void *source, void *destination, u32 count)
{
    s32 slot = find_dma_slot(source, destination);
    if (slot >= 0 && data_03002BC0[slot] == 0) {
        u32 control = count | 0xA2000000;

        data_03002BD0[slot].source = source;
        data_03002BD0[slot].destination = destination;
        data_03002BD0[slot].control = control;
        data_03002BD0[slot].state = 1;
        data_03002BD0[slot].flags = 0x80;
    }
    return slot;
}
