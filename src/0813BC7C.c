#include "ffta.h"

extern u16 data_030027B0[16];
extern u16 (*data_0200F37C)(u16 index);
extern void func_080033C8(u32 delay);
extern void func_0813AE30(void);

/* Complete [0x0813BC7C, 0x0813BCE4): 104 bytes, 42 instructions. */
void func_0813BC7C(u8 group)
{
    int i;

    for (i = 0; i < 16; i++) {
        if ((data_030027B0[i] >> 8) == group ||
            (data_030027B0[i] >> 8) == 0xff) {
            if (data_0200F37C(i)) {
                func_080033C8(10);
                if (data_0200F37C(i)) {
                    func_080033C8(10);
                    data_0200F37C(i);
                }
            }
        }
    }
    func_0813AE30();
}
