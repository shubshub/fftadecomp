#include "ffta.h"

typedef struct {
    u32 value;
    u8 unknown_04[0x324];
} Record080C4830;

typedef struct {
    u8 unknown_00[0x2968];
    Record080C4830 records[13];
    u16 count;
} RecordState080C4830;

/* Complete [0x080C4830, 0x080C486C): 60 bytes, 26 instructions. */
s16 func_080C4830(RecordState080C4830 *state, u32 *output)
{
    s32 index;

    for (index = 0; index < state->count; index++)
        *output++ = state->records[index].value;

    return (s16)state->count;
}
