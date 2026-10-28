#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x11A9];
    u8 active;
} State0805D1A4;

extern State0805D1A4 *data_0200F448;

/* 0805D1A4..0805D1C0: 28 bytes, 9 reachable instructions. */
u32 func_0805D1A4(void)
{
    return data_0200F448->active != 0;
}
