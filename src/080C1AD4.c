#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x54cc];
    u8 values[4];
    u8 mode : 4;
    u8 next : 4;
    u8 unknown_54d1[7];
    u16 field_54d8;
} State080C1AD4;

extern State080C1AD4 data_020101F8;

/* Target: complete [0x080C1AD4, 0x080C1B18), 68 bytes, 25 instructions. */
void func_080C1AD4(u16 value)
{
    State080C1AD4 *state = &data_020101F8;

    state->field_54d8 = value;
    state->values[state->next++] = 5;
}
