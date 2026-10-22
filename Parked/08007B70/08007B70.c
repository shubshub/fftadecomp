/* 0x08007B70 - 274 bytes */
#include "ffta.h"

typedef struct BoundaryState {
    double *horizontal;
    double *vertical;
    s32 count;
    u8 phase;
} BoundaryState;

s32 func_08007B70(BoundaryState *state, double *horizontal,
                  double *vertical, s32 count)
{
    s32 side;

    state->count = count;
    state->horizontal = horizontal;
    state->vertical = vertical;
    if (count <= 1) {
        return 0;
    }
    for (side = 1; side >= 0; side--) {
        horizontal[side] = horizontal[2] + horizontal[2] - horizontal[4 - side];
        vertical[side] = vertical[2] + vertical[2] - vertical[4 - side];
        horizontal[count + 3 - side] = horizontal[count + 1] + horizontal[count + 1]
                                      - horizontal[count - 1 + side];
        vertical[count + 3 - side] = vertical[count + 1] + vertical[count + 1]
                                    - vertical[count - 1 + side];
    }
    state->phase = 0;
    return (count - 1) * 8;
}
