#include "ffta.h"

typedef struct {
    u8 unknown_000[0x5DC];
    u8 value;
} State080A925C;

extern State080A925C data_0200F9E8;

/* 080A925C..080A9270: 02 48 03 49 40 18 00 21 01 70 70 47 E8 F9 00 02 DC 05 00 00. */
void func_080A925C(void)
{
    State080A925C *state = &data_0200F9E8;

    state->value = 0;
}
