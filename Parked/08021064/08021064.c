#include "ffta.h"

/* 0x08021064 .. 0x080210E4: 128 bytes. */
static inline s32 read_count(u8 *data)
{
    return data[0] | (data[1] << 8);
}

s32 func_08021064(u8 *list)
{
    u8 *entry = list + 2;
    s32 total = 0;
    s32 index;

    for (index = 0; index < read_count(list); index++, entry += 6) {
        if ((entry[1] >> 6) == 0) {
            switch (entry[3] >> 6) {
            case 0:
                total += 1;
                break;
            case 1:
                total += 4;
                break;
            case 2:
                total += 16;
                break;
            default:
                total += 64;
                break;
            }
        } else {
            switch (entry[3] >> 6) {
            case 0:
                total += 2;
                break;
            case 1:
                total += 4;
                break;
            case 2:
                total += 8;
                break;
            default:
                total += 32;
                break;
            }
        }
    }
    return total;
}
