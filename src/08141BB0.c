#include "ffta.h"

/* Complete [0x08141BB0, 0x08141BDE): 46 bytes, 23 instructions. */
const u8 *func_08141BB0(const u8 *source, const u8 *data, u32 count)
{
    u32 remaining = count - 1;
    if (count != 0) {
        do {
            if (*data++ != *source++)
                return data - 1;
        } while (remaining-- != 0);
    }
    return 0;
}
