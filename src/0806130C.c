#include "ffta.h"

extern u8 func_080C9540(u16 flag);
extern void func_080C9574(u16 flag, u16 enabled);

/* Complete target: [0x0806130C, 0x08061350), 68 bytes, 29 instructions. */
void func_0806130C(const u8 *entry)
{
    if (entry != 0 && *entry != 0) {
        u16 flag = *entry;

        flag |= 0x500;
        if (func_080C9540(flag) == 0) {
            func_080C9574(flag, 1);
            if (flag == 0x537)
                func_080C9574(0x582, 1);
        }
    }
}
