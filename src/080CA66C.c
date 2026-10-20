#include "ffta.h"

typedef struct {
    u8 unknown_00[0x24];
    s16 value_24;
    u8 unknown_26[4];
    u16 entries[5];
} StatObject;

s32 func_080CA7A4(u16 entry, u8 selector);

s32 func_080CA66C(const void *object, u8 enabled)
{
    const StatObject *state = object;
    s16 value = state->value_24;

    if (enabled) {
        s32 sum = 0;
        s32 index;

        for (index = 0; index < 5; index++) {
            if (state->entries[index] != 0)
                sum += func_080CA7A4(state->entries[index], 0x0C);
        }
        value += sum;
    }
    if (value > 999)
        return 999;
    return value;
}
