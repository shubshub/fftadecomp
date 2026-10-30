#include "ffta.h"

struct State08121E1C {
    u8 unknown_00[0x8D4];
    u32 field_8D4;
};

extern struct State08121E1C *data_020159CC;

/* Complete [0x08121E1C, 0x08121E30): 20 bytes, 6 reachable Thumb instructions.
 * 024800680249401800687047cc590102d4080000
 */
u32 func_08121E1C(void)
{
    return data_020159CC->field_8D4;
}
