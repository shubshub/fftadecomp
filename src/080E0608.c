#include "ffta.h"

typedef struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

/* 0x080E0608 - 66 bytes, including the middle literal pool.
 * Target: 10b5041c0904090c1b041b0c2180638018044014a08023811204121409040914521a
 *         62811004002806da0248e0805042608103e0ffff00000120e08010bc01bc0047
 */
void func_080E0608(InterpolationState *state, s16 start, s16 end, s16 duration)
{
    state->current = start;
    state->remaining = duration;
    state->error = duration >> 1;
    state->period = duration;
    state->distance = end - start;
    if (state->distance < 0) {
        state->step = -1;
        state->distance = -state->distance;
    } else {
        state->step = 1;
    }
}
