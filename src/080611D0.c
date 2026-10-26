#include "ffta.h"

/* 0x080611D0..0x080611EE: 30 bytes. */
extern void func_0802A2C0(u32 first, u32 second, u32 third, u32 fourth);
extern void func_0802A370(u32 first, u32 second, u32 third, u32 fourth);

void func_080611D0(void)
{
    func_0802A2C0(0x11, 1, 0x0D, 0x12);
    func_0802A370(0, 0, 0, 0);
}
