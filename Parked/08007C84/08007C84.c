#include "ffta.h"

typedef struct {
    double *x_values;
    double *y_values;
    s32 count;
    u8 phase;
    s32 index;
    s32 start;
    s32 end;
    double weights[4][8];
} InterpolationState;

/* Target: 0x08007C84, 790 bytes including the internal literal pool. */
s32 func_08007C84(InterpolationState *state, double *output_x, double *output_y)
{
    if (state->phase == 0) {
        s32 count = state->count;

        for (state->index = 0; state->index < 8; state->index++) {
            s32 sample = state->index;
            double fraction = sample * 0.125;
            double square = fraction * fraction;
            double cube = square * fraction;

            state->weights[0][sample] = cube / 6.0;
            state->weights[1][sample] = ((-cube + square + fraction) * 3.0 + 1.0) / 6.0;
            state->weights[2][sample] = (cube * 3.0 - square * 6.0 + 4.0) / 6.0;
            state->weights[3][sample] = ((square - fraction) * 3.0 - cube + 1.0) / 6.0;
        }
        state->start = 2;
        state->end = count + 1;
        state->index = 2;
        state->phase = 1;
    } else if (state->phase == 1) {
        s32 index = state->index;
        s32 end = state->end;

        if (index >= end) {
            state->phase = 2;
            return 0;
        } else {
            double *x_values = state->x_values;
            double *y_values = state->y_values;
            s32 start = state->start;
            s32 sample;

            for (sample = 0; sample < 8; sample++) {
                double horizontal = x_values[index + 2] * state->weights[0][sample]
                    + x_values[index + 1] * state->weights[1][sample]
                    + x_values[index] * state->weights[2][sample]
                    + x_values[index - 1] * state->weights[3][sample];
                double vertical = y_values[index + 2] * state->weights[0][sample]
                    + y_values[index + 1] * state->weights[1][sample]
                    + y_values[index] * state->weights[2][sample]
                    + y_values[index - 1] * state->weights[3][sample];

                output_x[(index - start) * 8 + sample] = horizontal;
                output_y[(index - start) * 8 + sample] = vertical;
            }
            output_x[(end - start) * 8] = x_values[end];
            output_y[(end - start) * 8] = y_values[end];
        }
        state->index = index + 1;
        if (state->index >= end) {
            state->phase = 2;
            return 0;
        }
    }
    return 1;
}
