#include "ffta.h"

extern void (*data_0836D4BC)(void *destination, const void *source, u32 size);

/* 0x0802807C: 120 bytes; separate interleaved tile rows in two blocks. */
void func_0802807C(u8 *destination, const u8 *source)
{
    s32 block;

    for (block = 0; block < 2; block++) {
        const u8 *second_source;
        u8 *second_destination;
        const u8 *first_source;
        u8 *first_destination;
        s32 row;

        second_source = source + 0x20;
        second_destination = destination + 0x80;
        first_source = source;
        first_destination = destination;
        for (row = 3; row >= 0; row--) {
            data_0836D4BC(first_destination, first_source, 0x20);
            data_0836D4BC(second_destination, second_source, 0x20);
            second_source += 0x40;
            second_destination += 0x20;
            first_source += 0x40;
            first_destination += 0x20;
        }
        source += 0x100;
        destination += 0x100;
    }
}
