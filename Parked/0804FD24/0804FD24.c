#include "ffta.h"

extern s32 func_081426B8(s32 numerator, s32 denominator);
extern s32 func_08142950(s32 numerator, s32 denominator);

/* Complete target [0x0804FD24, 0x0804FD60), 60 bytes.
 * 30b5041c0804050c00140a21f2f0c2fc0006000e002801d007494018208028040014
 * 0a21f2f002fe0006000e02494018608030bc01bc00471ed00000
 */
void func_0804FD24(u16 *output, u16 value)
{
    u32 first = (u8)func_081426B8((s16)value, 10);

    if (first != 0)
        first += 0xD01E;
    output[0] = first;
    output[1] = (u8)func_08142950((s16)value, 10) + 0xD01E;
}
