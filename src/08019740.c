#include "ffta.h"

struct Scene08019740 {
    u8 unknown_00[0xE];
    u16 value;
};

extern struct Scene08019740 g_state_020020D0;
extern void func_080142DC(u8 *text, u32 value, u32 digits);

u32 func_08019740(u8 *text)
{
    func_080142DC(text, g_state_020020D0.value, 3);
    return 0;
}
