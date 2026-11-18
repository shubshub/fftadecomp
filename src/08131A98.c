#include "ffta.h"

typedef struct {
    void *source;
    void *target;
    u8 unknown_08[4];
    u16 entry;
    u16 first;
    u8 unknown_10[0x16];
    u16 flags;
} Context;

extern s32 func_0813189C(const Context *context);

/* Evaluator slot 43, [0x08131A98, 0x08131AC0). */
s32 func_08131A98(const Context *context)
{
    s32 value = func_0813189C(context) * 3;

    if (value < -999)
        value = -999;
    if (value > 999)
        value = 999;
    return value;
}
