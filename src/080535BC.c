#include "ffta.h"

struct State080535BC {
    u8 unknown_0000[0x1D48];
    u8 entries[20];
};

extern struct State080535BC *data_0200F428;

/* Complete target: [0x080535BC, 0x080535E8), 44 bytes. */
void func_080535BC(void)
{
    u8 index;

    for (index = 0; index < 20; index++)
        data_0200F428->entries[index] = 0;
}
