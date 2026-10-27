#include "ffta.h"

typedef struct Appearance0802B368 Appearance0802B368;

extern void func_08016E1C(Appearance0802B368 *state, u8 first, u8 second);
extern void func_08016E4C(const Appearance0802B368 *state, u8 *destination,
                         u8 first);

/* Complete [0x0802B368, 0x0802B3A6): 62 bytes, 28 instructions. */
void func_0802B368(Appearance0802B368 *state, u8 *destination,
                   u8 first, u8 second)
{
    func_08016E1C(state, first, second);
    if (first)
        func_08016E4C(state, destination, 1);
    if (second)
        func_08016E4C(state, destination + 0xC0, 0);
}
