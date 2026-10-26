#include "ffta.h"

struct State08121DBC {
    u8 unknown_00[0x898];
    u32 field_898;
};

extern struct State08121DBC *data_020159CC;

/* Target: [0x08121DBC, 0x08121DD0), 20 bytes.
 * 024800680249401800687047cc59010298080000
 */
u32 func_08121DBC(void)
{
    return data_020159CC->field_898;
}
