/* Target 0x080E051C, 34 bytes:
 * 10b5041c002c08d025f744fb002804d0201c25f713fb002000e0201c10bc02bc0847
 */

#include "ffta.h"

u32 func_08005BB0(const void *object);
void func_08005B58(void *object);

void *func_080E051C(void *object)
{
    if (object != 0 && func_08005BB0(object) != 0) {
        func_08005B58(object);
        return 0;
    }
    return object;
}
