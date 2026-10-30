#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x54BB];
    u8 value;
} State080C153C;

extern State080C153C data_020101F8;

/* 0x080C153C..0x080C1550: 20 bytes, including alignment and two literals. */
u8 func_080C153C(void)
{
    return data_020101F8.value;
}
