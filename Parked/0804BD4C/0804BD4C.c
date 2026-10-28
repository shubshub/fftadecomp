#include "ffta.h"

typedef struct {
    s16 x;
    s16 y;
} Coordinate;

typedef struct {
    u8 count;
    u8 unknown_01[3];
    const s8 *coordinates;
} CoordinateSequence;

extern const CoordinateSequence data_083931B0[];

/* Complete target: [0x0804BD4C, 0x0804BDB0), 100 bytes. */
Coordinate func_0804BD4C(u8 reverse, u8 sequence, u8 index)
{
    Coordinate result;
    u8 count = data_083931B0[sequence].count;
    u16 offset = count;
    const s8 *coordinate;

    if (index >= offset) {
        result.x = 0;
        result.y = 0;
        return result;
    }

    if (reverse == 0) {
        offset = index * 2;
    } else {
        offset -= index + 1;
        offset *= 2;
    }

    coordinate = data_083931B0[sequence].coordinates + offset;
    result.x = coordinate[0];
    result.y = coordinate[1];
    return result;
}
