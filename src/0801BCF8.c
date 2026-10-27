#include "ffta.h"

extern void func_0801E5E0(u32 x, s16 y);
extern u16 func_0801B938(s16 x, s16 y);

/* 0801BCF8..0801BD2C: 52 bytes. */
u16 func_0801BCF8(s16 x, s16 y, u16 target_x, u16 target_y)
{
    func_0801E5E0(x, y);
    return func_0801B938((s16)target_x, (s16)target_y);
}
