/* 0x08008480 - 590 bytes */
#include "ffta.h"

void func_08008480(s32 count, const signed long long *coordinates,
                  const signed long long *values, signed long long *result,
                  signed long long *workspace)
{
    signed long long *intervals;
    signed long long *pivots;
    signed long long ratio;
    s32 index;

    while (count <= 2) {
    }
    intervals = workspace;
    pivots = workspace + count;
    result[0] = 0;
    result[count - 1] = 0;
    for (index = 0; index < count - 1; index++) {
        intervals[index] = coordinates[index + 1] - coordinates[index];
        pivots[index + 1] = ((values[index + 1] - values[index]) * 65536LL)
                            / intervals[index];
    }
    result[1] = pivots[2] - pivots[1] - ((intervals[0] * result[0]) >> 16);
    pivots[1] = (coordinates[2] - coordinates[0]) * 2;
    for (index = 1; index < count - 2; index++) {
        ratio = (intervals[index] * 65536LL) / pivots[index];
        result[index + 1] = pivots[index + 2] - pivots[index + 1]
                            - ((result[index] * ratio) >> 16);
        pivots[index + 1] = (coordinates[index + 2] - coordinates[index]) * 2
                            - ((intervals[index] * ratio) >> 16);
    }
    result[count - 2] -= (intervals[count - 2] * result[count - 1]) >> 16;
    for (index = count - 2; index > 0; index--) {
        result[index] = ((result[index] - ((intervals[index] * result[index + 1]) >> 16))
                         * 65536LL) / pivots[index];
    }
}
