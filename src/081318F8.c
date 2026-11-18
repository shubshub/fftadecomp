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
extern u32 func_08002804(void);

/* Evaluator slot 32, [0x081318F8, 0x0813192E). */
s32 func_081318F8(const Context *context)
{
    s32 base = func_0813189C(context);
    u32 roll = func_08002804();
    s32 result = base / 10 + (s16)((s16)roll % 11);

    if (result < 1)
        result = 1;
    return result;
}
