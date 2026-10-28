#include "ffta.h"

/* 0x080CBCE0..0x080CBD34: 84 bytes, including the literal pool. */
extern u16 data_02001F30[5];
extern u8 func_080CC7CC(void);

u8 func_080CBCE0(void)
{
    u8 i;
    u8 j;

    for (i = 0; i < 5; i++) {
        if (data_02001F30[i] == 0) {
            for (j = i + 1; j < 5; j++) {
                if (data_02001F30[j] != 0) {
                    data_02001F30[i] = data_02001F30[j];
                    data_02001F30[j] = 0;
                    break;
                }
            }
        }
    }
    return func_080CC7CC();
}
