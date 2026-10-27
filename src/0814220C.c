#include "ffta.h"

typedef unsigned long long DoubleWord;

typedef union {
    DoubleWord value;
    struct {
        u32 low;
        u32 high;
    } words;
} SplitWord;

/* 0814220C..08142242: 54 bytes, 27 instructions. */
DoubleWord func_0814220C(DoubleWord value, s32 count)
{
    SplitWord input, output;
    s32 remaining;

    if (count == 0)
        return value;

    input.value = value;
    remaining = 32 - count;
    if (remaining <= 0) {
        output.words.low = 0;
        output.words.high = input.words.low << -remaining;
    } else {
        u32 carry = input.words.low >> remaining;
        output.words.low = input.words.low << count;
        output.words.high = (input.words.high << count) | carry;
    }
    return output.value;
}
