#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1C0];
    u32 value_1C0;
    u32 value_1C4;
    u32 value_1C8;
    u32 value_1CC;
} Struct08148830;

void func_08148830(void)
{
    Struct08148830 *state = (Struct08148830 *)0x03005F30;

    state->value_1CC = 0;
    state->value_1C0 = 0;
    state->value_1C8 = 0xFFFF;
    state->value_1C4 = 0;
}
