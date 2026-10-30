#include "ffta.h"

typedef struct {
    s16 first;
    s16 second;
} Pair0809FD28;

extern s32 func_081426B8(s32 numerator, s32 denominator);

/* 0809FD28..0809FD86: f0b5474680b4031c0e1c151c002080460027701e80451cda1c1c0022a15e0423e05e0a1a002a00da52420220215e0623e05e081a002800da4042824200db101c291ca2f0a5fc804404340137701e8742e3db404608bc9846f0bc02bc0847. */
s32 func_0809FD28(const Pair0809FD28 *pairs, s32 count, s32 denominator)
{
    s32 total = 0;
    s32 index;

    for (index = 0; index < count - 1; index++) {
        s32 first;
        s32 second;

        first = pairs[index].first - pairs[index + 1].first;
        if (first < 0)
            first = -first;

        second = pairs[index].second - pairs[index + 1].second;
        if (second < 0)
            second = -second;

        if (first >= second)
            second = first;

        total += func_081426B8(second, denominator);
    }

    return total;
}
