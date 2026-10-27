#include "ffta.h"

/* 0x0801BD68..0x0801BDA4: 60 bytes. */
extern void func_0801E5E0(s16 x, s16 y);
extern u16 func_0801BB0C(s16 x, s16 y, u16 duration);

u16 func_0801BD68(s16 x, s16 y, u16 target_x, u16 target_y, u16 duration)
{
    func_0801E5E0(x, y);
    return func_0801BB0C((s16)target_x, (s16)target_y, duration);
}
