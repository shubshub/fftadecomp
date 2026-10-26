#include "ffta.h"

typedef struct {
    u8 unknown_00[0xAE];
    u8 flags;
} State080C7378;

extern State080C7378 data_02015738;

/* Complete [0x080C7378, 0x080C738C): 20 bytes, 7 instructions. */
void func_080C7378(void)
{
    data_02015738.flags |= 0x40;
}
