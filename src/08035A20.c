#include "ffta.h"

struct Record08035A20 {
    u8 value;
    u8 unknown_01[19];
};

struct State08035A20 {
    u8 unknown_000[0x67C];
    struct Record08035A20 *records;
};

extern struct State08035A20 *g_state_03002810;

/* Complete target: [0x08035A20, 0x08035A44), 36 bytes. */
u32 func_08035A20(u8 index)
{
    return g_state_03002810->records[index].value * 8;
}
