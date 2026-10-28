#include "ffta.h"

typedef struct {
    u32 flags;
    u8 unknown_04[0x2C];
    u16 first;
    u16 second;
} ValueState;

/* 08021D14..08021D40: 44 bytes. */
void func_08021D14(const ValueState *state, u16 *first, u16 *second)
{
    if ((state->flags & 0x800) == 0) {
        *first = *second = 0x100;
    } else {
        *first = state->first;
        *second = state->second;
    }
}
