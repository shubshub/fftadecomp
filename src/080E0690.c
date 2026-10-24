#include "ffta.h"

/* Target: 00b500210222805e002800d10121081c02bc0847 */

typedef struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

u8 func_080E0690(InterpolationState *state)
{
    return state->remaining == 0;
}
