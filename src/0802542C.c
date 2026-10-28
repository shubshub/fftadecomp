#include "ffta.h"

/* 0x0802542C..0x08025448: 28 bytes / 10 instructions. */
struct State0802542C {
    u8 unknown_00[3];
    u8 enabled;
};

extern struct State0802542C *data_0200F438;
extern void func_080253B0(u8 selector, u32 mode);

void func_0802542C(u8 selector)
{
    data_0200F438->enabled = 0;
    func_080253B0(selector, 0);
}
