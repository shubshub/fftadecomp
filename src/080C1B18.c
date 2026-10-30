#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x54D8];
    u16 value;
} State080C1B18;

extern State080C1B18 data_020101F8;

/* 0x080C1B18..0x080C1B2C: 20 bytes, including alignment and two literals. */
u16 func_080C1B18(void)
{
    return data_020101F8.value;
}
