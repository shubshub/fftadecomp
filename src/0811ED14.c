#include "ffta.h"

/* Target 0x0811ED14..0x0811ED40 (44 bytes):
 * 10b5041c002c0dd0e6f648ff002801d0012000e00020002804d0201ce6f612ff002000e0201c10bc02bc0847
 */
extern u32 func_08005BB0(const void *object);
extern void func_08005B58(void *object);

static inline u8 object_is_state_2(const void *object)
{
    if (func_08005BB0(object))
        return 1;
    return 0;
}

void *func_0811ED14(void *object)
{
    if (object != 0) {
        if (object_is_state_2(object)) {
            func_08005B58(object);
            return 0;
        }
    }
    return object;
}
