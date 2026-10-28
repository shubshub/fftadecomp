#include "ffta.h"

typedef signed long long s64;

typedef union {
    s64 value;
    struct {
        u32 low;
        s32 high;
    } words;
} Signed64;

/* Complete [0x0814435C, 0x08144378): 28 bytes, 14 instructions. */
s32 func_0814435C(s64 left, s64 right)
{
    Signed64 a, b;
    a.value = left;
    b.value = right;
    if (a.words.high < b.words.high)
        return 0;
    if (a.words.high > b.words.high)
        return 2;
    if (a.words.low < b.words.low)
        return 0;
    if (a.words.low > b.words.low)
        return 2;
    return 1;
}
