#include "ffta.h"

extern u32 func_08005BB0(const void *object);
extern void func_08005B58(void *object);

static inline u8 object_is_state_2(const void *object)
{
    if (func_08005BB0(object))
        return 1;
    return 0;
}

/* Target 0x080DFED8..0x080DFF04 (44 bytes):
 * 10 b5 04 1c 00 2c 0d d0 25 f7 66 fe 00 28 01 d0
 * 01 20 00 e0 00 20 00 28 04 d0 20 1c 25 f7 30 fe
 * 00 20 00 e0 20 1c 10 bc 02 bc 08 47
 */
void *func_080DFED8(void *task)
{
    if (task != 0) {
        if (object_is_state_2(task)) {
            func_08005B58(task);
            return 0;
        }
    }
    return task;
}
