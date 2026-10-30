#include "ffta.h"

typedef struct {
    u8 unknown_00[0x26];
    u16 flags;
} State0812F39C;

extern State0812F39C data_0200F3F0;

/* Complete [0x0812F39C, 0x0812F3B0): 20 bytes, 7 instructions.
 * 034a01218140d08c0143d18470470000f0f30002
 * The observed caller uses indices 0 through 2.
 */
void func_0812F39C(s32 index)
{
    data_0200F3F0.flags |= 1u << index;
}
