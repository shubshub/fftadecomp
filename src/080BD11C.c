#include "ffta.h"

/* 0x080BD11C..0x080BD130: 20 bytes, including the literal pool. */
typedef struct {
    u8 unknown_00[0x1CA];
    u8 value;
} State;

extern State *data_020101F0;

void func_080BD11C(u8 value)
{
    data_020101F0->value = value;
}
