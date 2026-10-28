#include "ffta.h"

typedef struct BufferState08010FD0 {
    u8 unknown_00[0x18];
    u8 data[0x20];
} BufferState08010FD0;

extern void (*const data_0836D4BC)(void *destination, const void *source,
                                  s32 size);

/* Complete [0x08010FD0, 0x08010FEC): 28 bytes, 11 instructions. */
void func_08010FD0(const BufferState08010FD0 *state, void *destination)
{
    data_0836D4BC(destination, state->data, sizeof(state->data));
}
