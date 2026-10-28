#include "ffta.h"

/* 0x0812F2A4..0x0812F2CC: 40 bytes, 17 instructions. */
typedef struct State State;

extern State data_0200F3F0;
extern void func_0812F230(State *state, u16 first, u16 second, u8 kind);

void func_0812F2A4(u16 first, u16 second, u8 kind)
{
    func_0812F230(&data_0200F3F0, first, second, kind);
}
