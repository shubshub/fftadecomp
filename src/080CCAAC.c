#include "ffta.h"

/* 0x080CCAAC..0x080CCAD8: 44 bytes, 20 instructions, including a pool. */
extern u16 data_02001F3C[20];

void func_080CCAAC(u16 value)
{
    u8 index = 0;
    u16 *entries = data_02001F3C;

    do {
        if (entries[index] == 0) {
            entries[index] = value;
            break;
        }
        index++;
    } while (index < 20);
}
