#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u8 unknown_02[12];
    u16 unknown_0e;
} State08029514;

extern State08029514 *data_0200F438;

/* 0x08029514..0x08029528: 20 complete bytes, including alignment and literal. */
void func_08029514(void)
{
    State08029514 *state = data_0200F438;

    state->unknown_0e = 0;
    state->unknown_00 = 1;
}
