#include "ffta.h"

/* Action evaluator slot 11, 0x081315F8..0x0813163A.
 * 70b5041c60689cf725fa0006002801d0002013e06068008b85086e00e18c10200840002808d1d1f6f1f800040014711c11f092f9401901e07010281870bc02bc0847
 */
struct Unit {
    u8 unknown00[0x18];
    u16 value;
};

struct ActionState {
    struct Unit *source;
    struct Unit *target;
    u8 unknown08[0x1E];
    u16 flags;
};

extern u8 func_080CDA4C(const void *object);
extern u32 func_08002804(void);

s32 func_081315F8(struct ActionState *state)
{
    s32 minimum;
    s32 range;

    if (func_080CDA4C(state->target))
        return 0;

    minimum = state->target->value / 4;
    range = minimum * 2;
    if (state->flags & 0x10)
        return minimum + (range >> 1);
    return (s16)func_08002804() % (range + 1) + minimum;
}
