#include "ffta.h"

extern s32 func_08141874(s32 dividend, s32 divisor);

/* 0x08007244 - 20 bytes */
s16 func_08007244(s16 dividend, s16 divisor)
{
    return (s16)func_08141874((s32)((u32)dividend << 16), divisor);
}
