#include "ffta.h"

union DoubleWord {
    unsigned long long value;
    struct {
        u32 low;
        u32 high;
    } words;
};

unsigned long long func_08144378(unsigned long long value, s32 shift)
{
    union DoubleWord input;
    union DoubleWord result;
    s32 remaining;

    if (shift == 0)
        return value;

    input.value = value;
    remaining = 32 - shift;
    if (remaining <= 0) {
        result.words.high = 0;
        result.words.low = input.words.high >> -remaining;
    } else {
        u32 carry = input.words.high << remaining;

        result.words.high = input.words.high >> shift;
        result.words.low = (input.words.low >> shift) | carry;
    }
    return result.value;
}
