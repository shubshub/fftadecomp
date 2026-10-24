#include "ffta.h"

struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
};

/* 0x080E064C - 68 bytes.
 * Target: f0b5021c53880221505e002817d090885189411a918008049c4600280cdad788168915880b1cec19251c99190b1c08040028f8db91801480604601385080f0bc01bc0047
 */
void func_080E064C(struct InterpolationState *state)
{
    if (state->remaining != 0) {
        state->error -= state->distance;
        while (state->error < 0) {
            state->current += state->step;
            state->error += state->period;
        }
        state->remaining--;
    }
}
