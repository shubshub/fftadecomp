#include "ffta.h"

/* 0x080DD670..0x080DD682: 18 bytes. */
typedef struct {
    u8 unknown_00[0x14];
    u8 bits[32];
} PackedBits080DD670;

extern u8 func_080A883C(const PackedBits080DD670 *state, u8 index);

u8 func_080DD670(const PackedBits080DD670 *state, u8 index)
{
    return func_080A883C(state, index);
}
