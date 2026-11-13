#include "ffta.h"

// Target: 0x08000670..0x080006D0, complete 96-byte body including the literal pool.
typedef struct {
    u16 held;
    u16 unknown_02;
    u16 pressed;
    u8 unknown_06;
    u8 flags;
    u16 unknown_08;
    u8 unknown_0A;
    u8 unknown_0B;
} Input;

extern Input data_03000000;

void func_08000670(void)
{
    data_03000000.flags = 2;
    data_03000000.unknown_08 = 0xF0;
    data_03000000.unknown_0A = 0xF;
    data_03000000.unknown_0B = 4;
}
