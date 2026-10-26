#include "ffta.h"

/* Complete [0x0806EC20, 0x0806EC60): 64 bytes, 30 instructions. */
typedef struct {
    u8 status;
    u8 entries[6];
    u8 count;
    u8 field_08;
    u8 field_09;
    u8 unknown_0a[2];
    const void *resource;
    u8 unknown_10[0x68];
    u8 x;
    u8 y;
} DisplayState;

extern const u8 data_08393B40[6];

void func_0806EC20(DisplayState *state, const void *resource, u8 x, u8 y,
                   u8 field_08, u8 field_09)
{
    u8 i;

    state->status = 0;
    state->resource = resource;
    state->x = x;
    state->y = y;
    state->field_08 = field_08;
    state->field_09 = field_09;
    state->count = 6;
    for (i = 0; i < 6; ++i)
        state->entries[i] = data_08393B40[i];
}
