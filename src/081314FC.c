#include "ffta.h"

/* Action evaluator slot 3, 0x081314FC..0x0813151A.
 * 00b540689cf7a4fa0006002804d1014803e00000e7030000002002bc0847
 */
struct ActionState {
    void *source;
    void *target;
};

extern u8 func_080CDA4C(const void *object);

s32 func_081314FC(struct ActionState *state)
{
    if (func_080CDA4C(state->target))
        return 0;
    return 999;
}
