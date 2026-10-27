#include "ffta.h"

/* 08018C24..08018C92: 110 bytes, 55 instructions. */
u16 func_08018C24(u8 *destination, const u8 *source)
{
    u8 *output = destination;

    if (source == 0 || destination == 0)
        return 0;

    if (*source == 1) {
        source++;
        while (*source) {
            *output = 0x80;
            output++;
            *output = *source - 1;
            source++;
            output++;
        }
    } else if (*source) {
        u32 prefix_mask = 0x80;

        do {
            u32 value = *source;

            if (prefix_mask & value) {
                *output = value;
                source++;
                output++;
                *output = *source;
            } else {
                *output = value;
            }
            source++;
            output++;
        } while (*source);
    }
    *output = 0;
    return output - destination;
}
