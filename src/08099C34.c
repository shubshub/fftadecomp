#include "ffta.h"

/* 0x08099C34..0x08099C64: 48 bytes. */
typedef struct {
    u8 unknown_00[0x44];
    u32 fallback;
    u32 unknown_48;
    u32 values[2];
} ValueState;

s32 func_08021C3C(u32 value);

s32 func_08099C34(ValueState *state)
{
    s32 index;
    u32 value;
    s32 result;

    for (index = 0; index < 2; ++index) {
        value = state->values[index];
        if (value != 0) {
            result = func_08021C3C(value);
            if (result < 0)
                return -1;
            return result;
        }
    }

    value = state->fallback;
    if (value == 0)
        return -1;
    result = func_08021C3C(value);
    if (result < 0)
        return -1;
    return result;
}
