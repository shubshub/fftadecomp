#include "ffta.h"

typedef struct {
    u8 unknown_000[0x102];
    u8 field_102;
    u8 field_103;
} State080D2F0C;

/* 0x080D2F0C..0x080D2F2C:
 * 06 4A 81 18 01 3A 80 18 00 78 40 00 09 78 40 18
 * 40 10 01 30 00 04 00 0C 70 47 00 00 03 01 00 00. */
u16 func_080D2F0C(const State080D2F0C *state)
{
    return (state->field_103 + state->field_102 * 2) / 2 + 1;
}
