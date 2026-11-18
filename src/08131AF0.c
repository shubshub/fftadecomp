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

/* Evaluator slot 45, [0x08131AF0, 0x08131B20). */
s32 func_08131AF0(const Context *context)
{
    s32 value = func_0813189C(context);
    s32 magnitude = value < 0 ? -value : value;

    if (magnitude > 3)
        value >>= 2;

    if (value < -999)
        value = -999;
    if (value > 999)
        value = 999;
    return value;
}
