#include "ffta.h"

struct Scene08019740 {
    u8 unknown_00[0xE];
    u16 value;
};

extern struct Scene08019740 g_state_020020D0;
extern u16 func_080142DC(void *destination, u32 number, u32 field_width);

u32 func_08019740(u8 *text)
{
    func_080142DC(text, g_state_020020D0.value, 3);
    return 0;
}
