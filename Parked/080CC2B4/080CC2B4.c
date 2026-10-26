#include "ffta.h"

extern u16 data_02001F3C[];

/* Complete [0x080CC2B4, 0x080CC300): 76 bytes, 36 instructions. */
void func_080CC2B4(void)
{
    u8 index;

    for (index = 0; index < 20; index++) {
        if (data_02001F3C[index] == 0) {
            u8 next;

            for (next = index + 1; next < 20; next++) {
                if (data_02001F3C[next] != 0) {
                    data_02001F3C[index] = data_02001F3C[next];
                    data_02001F3C[next] = 0;
                    break;
                }
            }
        }
    }
}
