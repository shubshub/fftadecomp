#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u32 values[17];
    u8 unknown_4C[2];
    s16 index;
} IndexedValues;

/* 0x080A86EC..0x080A86FE: 18 bytes. */
u32 func_080A86EC(const IndexedValues *state)
{
    return state->values[state->index];
}
