#include "ffta.h"

union DoubleWord {
    long long value;
    struct {
        u32 low;
        u32 high;
    } words;
};

long long func_08142A94(long long value)
{
    union DoubleWord input;
    union DoubleWord result;

    input.value = value;
    result.words.low = -input.words.low;
    result.words.high = -input.words.high - (result.words.low != 0);
    return result.value;
}
