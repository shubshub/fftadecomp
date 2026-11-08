#include "ffta.h"

/* func_08070260: [0x08070260, 0x080702E8), 136 bytes */

void func_08070260(u16 *src, u16 *dst, u8 denominator, u8 numerator)
{
    u8 i;

    for (i = 0; i < 16; i++) {
        dst[i] = ((((src[i] >> 10) & 0x1F) * numerator / denominator) << 15)
               + ((((src[i] >> 5) & 0x1F) * numerator / denominator) << 5)
               + ((src[i] & 0x1F) * numerator / denominator);
    }
}
