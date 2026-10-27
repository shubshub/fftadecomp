#include "ffta.h"

/* 0x0801BD2C..0x0801BD68: 60 bytes. */
extern void func_0801E5E0(s16 x, s16 y);
extern u16 func_0801BA20(s16 x, s16 y, u16 speed);

u16 func_0801BD2C(s16 x, s16 y, u16 target_x, u16 target_y, u16 speed)
{
    func_0801E5E0(x, y);
    return func_0801BA20((s16)target_x, (s16)target_y, speed);
}
