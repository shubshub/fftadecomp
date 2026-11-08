#include "ffta.h"

/* 0x080A9448..0x080A946C: 36 bytes.
 * 00b581b0054900200090086d04496a461ef032fc009801b002bc0847e8f90002b1950a08
 */

/* 0x080A9448..0x080A946C: 36 bytes, including literal pools. */
typedef struct {
    u8 unknown_00[0x50];
    void *tree;
} AnimationGlobals080A9448;

extern AnimationGlobals080A9448 data_0200F9E8;
s32 func_080A95B0(void *node, s32 *result);
void func_080C7CC0(void *tree, s32 (*callback)(void *, s32 *), s32 *result);

s32 func_080A9448(void)
{
    AnimationGlobals080A9448 *state = &data_0200F9E8;
    s32 result = 0;

    func_080C7CC0(state->tree, func_080A95B0, &result);
    return result;
}
