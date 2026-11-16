#include "ffta.h"

extern u8 data_03000ED0[];
extern void func_08003398(void);

/* Complete target [0x080231C0, 0x080231D8), 24 bytes:
 * 00b50448a32101705d214170e0f7e4f8fce70000d00e0003
 */
void func_080231C0(void)
{
    data_03000ED0[0] = 0xA3;
    data_03000ED0[1] = 0x5D;
    for (;;)
        func_08003398();
}
