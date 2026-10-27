#include "ffta.h"

struct ScaledValue080CCC6C {
    u8 unknown_00[9];
    u8 level;
    u8 unknown_0a[0xE6];
    u8 scale;
};

static inline u32 thousands(u8 units)
{
    return units * 1000u;
}

/* Complete [0x080CCC6C, 0x080CCCA0): 52 bytes, 23 instructions. */
u32 func_080CCC6C(struct ScaledValue080CCC6C *state)
{
    u32 tier = (u8)(state->level / 10u);
    u32 multiplier = tier * 2 + 1;
    u32 value = multiplier * thousands(state->scale);

    if (value > 99999)
        value = 99999;
    return value;
}
