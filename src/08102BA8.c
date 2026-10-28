#include "ffta.h"

/* Target 0x08102BA8..0x08102BD4 (44 bytes):
 * 10b5041c002c0dd002f7feff002801d0012000e00020002804d0201c02f7c8ff002000e0201c10bc02bc0847
 */
extern u32 func_08005BB0(const void *handle);
extern void func_08005B58(void *handle);

static inline u8 handle_predicate(const void *handle)
{
    if (func_08005BB0(handle))
        return 1;
    return 0;
}

void *func_08102BA8(void *handle)
{
    if (handle != 0) {
        if (handle_predicate(handle)) {
            func_08005B58(handle);
            return 0;
        }
    }
    return handle;
}
