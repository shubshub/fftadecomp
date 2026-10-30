#include "ffta.h"

typedef struct {
    u8 unknown_00[0x17];
    u8 value;
} State08060DE0;

extern State08060DE0 *data_0200F44C;

/* 08060DE0..08060DEC: 01 48 00 68 C0 7D 70 47 4C F4 00 02. */
u8 func_08060DE0(void)
{
    return data_0200F44C->value;
}
