/* 0x08007C84 - 790 bytes: [0x08007C84, 0x08007F9A), 339 instructions,
 * 40 bytes of internal double literals at 0x08007DBC. */
#include "ffta.h"

/* BoundaryState of src/0809AEF8.c, which passes it to func_08007B70; the
 * caller at 0x0809BF16-0x0809BF24 passes the same member (+0x148) here.
 * The fields after phase are the 0x10C bytes that follow it there. */
typedef struct BoundaryState {
    double *horizontal;
    double *vertical;
    s32 count;
    u8 phase;
    s32 index;
    s32 start;
    s32 end;
    double weights[4][8];
} BoundaryState;

s32 func_08007C84(BoundaryState *state, double *out_horizontal, double *out_vertical)
{
    /* The step is the left operand of __muldf3 (0.125 loaded into r0:r1 at
     * 0x08007CBA after the conversion moves to r2:r3); a literal is folded
     * to the right operand. */
    double step = 0.125;
    s32 sample;

    switch (state->phase) {
    case 0:
        for (state->index = 0; state->index < 8; state->index++) {
            double t = step * state->index;
            double t2;
            double t3;

            /* The first store's address (0x08007CC6) is formed before t * t
             * (0x08007CD0): the powers are computed inside this statement. */
            state->weights[0][state->index] = (t3 = (t2 = t * t) * t) / 6.0;
            state->weights[1][state->index] = ((-t3 + t2 + t) * 3.0 + 1.0) / 6.0;
            state->weights[2][state->index] = (t3 * 3.0 - t2 * 6.0 + 4.0) / 6.0;
            state->weights[3][state->index] = ((t2 - t) * 3.0 - t3 + 1.0) / 6.0;
        }
        state->start = 2;
        state->end = state->count + 1;
        state->index = 2;
        state->phase = 1;
        break;
    case 1:
        if (state->index >= state->end) {
            state->phase = 2;
            return 0;
        }
        /* The counter runs up from 0 and exits after the increment
         * (0x08007F3C-0x08007F44); a for loop is reversed into a count-down. */
        sample = 0;
        while (1) {
            double x = state->horizontal[state->index + 2] * state->weights[0][sample]
                + state->horizontal[state->index + 1] * state->weights[1][sample]
                + state->horizontal[state->index] * state->weights[2][sample]
                + state->horizontal[state->index - 1] * state->weights[3][sample];
            double y = state->vertical[state->index + 2] * state->weights[0][sample]
                + state->vertical[state->index + 1] * state->weights[1][sample]
                + state->vertical[state->index] * state->weights[2][sample]
                + state->vertical[state->index - 1] * state->weights[3][sample];

            out_horizontal[(state->index - state->start) * 8 + sample] = x;
            out_vertical[(state->index - state->start) * 8 + sample] = y;

            if (++sample >= 8)
                break;
        }
        out_horizontal[(state->end - state->start) * 8] = state->horizontal[state->end];
        out_vertical[(state->end - state->start) * 8] = state->vertical[state->end];
        state->index++;
        if (state->index >= state->end) {
            state->phase = 2;
            return 0;
        }
        return 1;
    }
    return 1;
}
