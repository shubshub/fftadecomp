/* Target 0x080E0570, 76 bytes:
 * f0b5474680b4804609040e0c01270025b54215d2a80041464418206800280ad025f70efb002805d0206825f7ddfa0020206000e00027681c0004050cb542e9d3381c08bc9846f0bc02bc0847
 */

#include "ffta.h"

u32 func_08005BB0(const void *object);
void func_08005B58(void *object);

u32 func_080E0570(void **slots, u16 count)
{
    u32 complete = 1;
    u16 index;

    for (index = 0; index < count; index++) {
        if (slots[index] != 0) {
            if (func_08005BB0(slots[index]) != 0) {
                func_08005B58(slots[index]);
                slots[index] = 0;
            } else {
                complete = 0;
            }
        }
    }
    return complete;
}
