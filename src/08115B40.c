#include "ffta.h"

/* Target 0x08115B40..0x08115B6C (44 bytes):
 * 10b5041c002c0dd0f0f632f8002801d0012000e00020002804d0201ceff6fcff002000e0201c10bc02bc0847
 */
extern u32 func_08005BB0(const void *object);
extern void func_08005B58(void *object);

static inline u8 object_is_state_2(const void *object)
{
    if (func_08005BB0(object))
        return 1;
    return 0;
}

void *func_08115B40(void *object)
{
    if (object != 0) {
        if (object_is_state_2(object)) {
            func_08005B58(object);
            return 0;
        }
    }
    return object;
}
