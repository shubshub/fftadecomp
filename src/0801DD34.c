#include "ffta.h"

typedef struct ParameterState0801DD34 {
    u8 unknown_00[2];
    u16 selector;
    u16 first;
    u8 unknown_06[6];
    u16 second;
    u16 third;
    u32 fourth;
    u32 derived;
} ParameterState0801DD34;

extern ParameterState0801DD34 data_02007F20;

/* Complete [0x0801DD34, 0x0801DD68): 52 bytes, 23 instructions. */
void func_0801DD34(u16 first, u16 second, u16 third, u32 fourth)
{
    ParameterState0801DD34 *state = &data_02007F20;

    if (state->selector != 0xFF) {
        state->first = first;
        state->second = second;
        state->third = third;
        state->fourth = fourth;
        state->derived = fourth + state->first - 160;
    }
}
