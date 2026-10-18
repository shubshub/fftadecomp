#include "ffta.h"

typedef struct {
    void *first;
    u8 *source;
    u16 count;
    u8 unknown_0A[2];
    u16 *data;
    u16 index;
    u16 field_12;
    u16 field_14;
    u8 field_16;
    u8 unknown_17;
    u16 field_18;
} State08135FFC;

void func_08135FFC(State08135FFC *state, void *first, u8 *source,
                   u16 index, u8 value)
{
    u16 *data;

    state->first = first;
    state->source = source;
    state->index = index;
    state->field_12 = 0;
    state->field_14 = 0;
    state->field_16 = value;
    state->field_18 = 0;
    data = (u16 *)(source + ((u32 *)source)[state->index]);
    state->count = *data;
    state->data = data + 1;
}
