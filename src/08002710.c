#include "ffta.h"

extern u32 data_03000930[2];
extern u32 data_030009C4;
extern void func_08002768(void);
extern void func_08003410(void);

/* Target: [0x08002710, 0x08002768), 88 bytes, 25 instructions. */
void func_08002710(void)
{
    if (data_03000930[0] == 0xa51d && data_03000930[1] == 0xc269)
        data_030009C4 = 1;
    else
        data_030009C4 = 0;

    func_08002768();
    func_08003410();

    data_03000930[0] = 0xa51d;
    data_03000930[1] = 0xc269;
}
