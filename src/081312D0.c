#include "ffta.h"

struct ActionContext;
extern u8 func_08131220(const struct ActionContext *context);

/* Action evaluator table 0x083A8678, slot 26. */
u8 func_081312D0(const struct ActionContext *context)
{
    s32 chance = func_08131220(context);

    if (chance < 100)
        chance /= 2;
    return chance;
}
