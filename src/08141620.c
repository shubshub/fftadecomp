#include "ffta.h"

extern u8 data_020084D8;
extern u8 data_0200F2E0[];
extern u8 data_0200F320[];
extern void func_08145990(void *player);

/* Target: [0x08141620, 0x0814164C), 44 bytes, 13 instructions. */
void func_08141620(void)
{
    if (data_020084D8 & 2) {
        func_08145990(data_0200F2E0);
        func_08145990(data_0200F320);
    }
}
