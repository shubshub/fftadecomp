#include "ffta.h"

struct State08121DE4 {
    u8 unknown_00[0x89C];
    u32 field_89C;
};

extern struct State08121DE4 *data_020159CC;

/* Complete [0x08121DE4, 0x08121DF8): 20 bytes, 6 reachable Thumb instructions.
 * 024800680249401800687047cc5901029c080000
 */
u32 func_08121DE4(void)
{
    return data_020159CC->field_89C;
}
