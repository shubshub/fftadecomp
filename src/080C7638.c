#include "ffta.h"

struct State080C7638;

extern struct State080C7638 data_020158B0;
extern u32 func_080C7078(struct State080C7638 *state, u32 value);

/* 0x080C7638..0x080C7650: 24 complete bytes, including alignment and literal. */
u8 func_080C7638(void)
{
    return func_080C7078(&data_020158B0, 0);
}
