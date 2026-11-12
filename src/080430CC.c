#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u16 *destination;
    u8 unknown_0C[9];
    u8 width;
    u8 rows;
    u8 unknown_17[7];
    u8 destination_stride;
} State080430CC;

extern void func_0814186C(const void *source, void *destination, u32 control);

/* Complete target [0x080430CC, 0x08043120): 84 bytes, no literal pool. */
void func_080430CC(State080430CC *state)
{
    u16 *destination = state->destination;
    u32 size = state->width * 2;
    s32 row;

    for (row = 0; row < state->rows * 2; row++) {
        u16 fill;
        u16 *source = &fill;
        *source = 0;
        func_0814186C(source, destination, 0x01000000 | (size >> 1));
        destination += state->destination_stride;
    }
}
