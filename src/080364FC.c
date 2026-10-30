/* Target: [0x080364FC, 0x0803652C), 48 bytes.
 * 10b540181f210cf125fa041c1c2c0bd0092c09d02006000efff7d2ff012149428842
 * 01d1201c00e0002010bc02bc0847
 */

#include "ffta.h"

extern s32 func_08142950(s32 numerator, s32 denominator);
extern s32 func_080364BC(u8 type);

s32 func_080364FC(s32 first, s32 second)
{
    s32 value = func_08142950(first + second, 31);

    if (value != 28 && value != 9) {
        if (func_080364BC((u8)value) == -1)
            return value;
    }
    return 0;
}
