#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u8 bits[32];
} PackedBits;

/* 0x080A883C..0x080A8856: 26 bytes. */
u8 func_080A883C(const PackedBits *state, u8 index)
{
    u32 byte_index = index >> 3;
    u32 bit_index = index & 7;

    return (state->bits[byte_index] >> bit_index) & 1;
}
