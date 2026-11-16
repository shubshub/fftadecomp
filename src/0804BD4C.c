#include "ffta.h"

/* Complete target: [0x0804BD4C, 0x0804BDB0), 100 bytes, 47 instructions:
 * f0b5061c0906090e8c461206170e1b061b0e1d1c0449f80040180078021c934204d300
 * 2419e00000b03139086046002801d15a0003e0681c101a4004020cf800043140180068
 * 801800214156090440780006001600040c0c04433460301cf0bc02bc0847
 */

typedef struct {
    s16 x;
    s16 y;
} Offset;

typedef struct {
    u8 count;
    u8 unknown_01[3];
    const s8 *coordinates;
} CoordinateSequence;

extern const CoordinateSequence data_083931B0[];

Offset func_0804BD4C(u8 reverse, u8 sequence, u8 index)
{
    Offset result;
    u8 count = data_083931B0[sequence].count;
    u16 offset;
    const s8 *coordinate;

    if (index >= count) {
        result.x = 0;
        result.y = 0;
        return result;
    }

    if (reverse == 0)
        offset = index * 2;
    else
        offset = (count - 1 - index) * 2;

    coordinate = data_083931B0[sequence].coordinates + offset;
    result.x = coordinate[0];
    result.y = coordinate[1];
    return result;
}
