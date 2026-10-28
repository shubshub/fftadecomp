#include "ffta.h"

typedef struct BlockState08016E4C {
    u8 unknown_00[0x14];
    u16 flags;
    u8 unknown_16[7];
    u8 first;
    u8 second;
} BlockState08016E4C;

extern u32 func_08018524(u8 *destination, u16 code, u8 variant);

/* Complete [0x08016E4C, 0x08016E86): 58 bytes, 28 instructions. */
void func_08016E4C(const BlockState08016E4C *state, u8 *destination,
                   u8 first)
{
    u8 variant;
    u16 code;

    if (first != 0) {
        variant = state->first & 0x7F;
        code = 0x3E;
    } else {
        variant = state->second & 0x7F;
        code = 0x44;
    }
    if (state->flags & 0x800)
        code = 0x4A;

    func_08018524(destination, code, variant);
}
