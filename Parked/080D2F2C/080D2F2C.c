#include "ffta.h"

/* Complete target: [0x080D2F2C, 0x080D2F78), 76 bytes.
 * 10b500230a48021c84328424640017211078002800d00133121901390029f7da052b
 * 09dd03480021f6f70efb08e0000000000002a705000003480121f6f704fb10bc01bc
 * 00470000a7050000
 */
extern u8 g_state_02000000[];
extern void func_080C9574(u16 bitIndex, u16 enabled);

void func_080D2F2C(void)
{
    s32 count = 0;
    const u8 *entry = g_state_02000000;
    s32 remaining;

    entry += 0x84;
    for (remaining = 23; remaining >= 0; remaining--) {
        if (*entry != 0)
            count++;
        entry += 0x108;
    }
    if (count > 5)
        func_080C9574(0x5A7, 0);
    else
        func_080C9574(0x5A7, 1);
}
