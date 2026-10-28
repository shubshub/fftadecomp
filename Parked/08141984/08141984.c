#include "ffta.h"

typedef void (*TimerCallback)(void);

extern u8 data_03005E40;
extern volatile u16 *data_03005E44;
extern volatile u16 data_04000100[8];
extern void func_0814195C(void);

/* Complete [0x08141984, 0x081419BE): 58 bytes, 21 instructions. */
u32 func_08141984(u8 timer, TimerCallback *callback)
{
    if (timer > 3)
        return 1;
    data_03005E40 = timer;
    data_03005E44 = &data_04000100[data_03005E40 * 2];
    *callback = func_0814195C;
    return 0;
}
