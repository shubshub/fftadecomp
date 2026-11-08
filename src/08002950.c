#include "ffta.h"

/* Complete target [0x08002950, 0x080029CC): 124 bytes. */
s16 func_08002950(const u16 *text)
{
    s16 negative = 0;
    s16 value = 0;
    const u16 digit_bias = -'0';

    while ((u8)*text == '\t' || *text == ' ')
        text++;
    if ((*text & 0xFF) == '-') {
        negative = 1;
        text++;
    }
    while ((u16)((*text & 0xFF) - '0') <= 9) {
        value = value * 10 + ((*text & 0xFF) + digit_bias);
        text++;
    }
    if (negative)
        return -value;
    return value;
}
