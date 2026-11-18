#include "ffta.h"

/* Action evaluator slot 10, 0x081315D4..0x081315F8.
 * 00b500f061f980000449884200da081c0349884200dd081c02bc084719fcffffe7030000
 */
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

s32 func_081315D4(Context *context)
{
    s32 value = func_0813189C(context) * 4;

    if (value < -999)
        value = -999;
    if (value > 999)
        value = 999;
    return value;
}
