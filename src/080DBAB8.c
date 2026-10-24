/* 0x080DBAB8 - 90 bytes
 * Target: f0b5474680b4061c090601270025090e8d421cd28846a900881900680c1c002810d02af769f8002801d0012000e00020002806d0a41920682af732f80020206000e00027681c0004050c4545e3d3381c08bc9846f0bc02bc0847
 */
#include "ffta.h"

extern u32 func_08005BB0(const void *object);
extern void func_08005B58(void *object);

static inline u8 object_is_state_2(const void *object)
{
    if (func_08005BB0(object))
        return 1;
    return 0;
}

u8 func_080DBAB8(void **objects, u32 count)
{
    u8 length = (u8)count;
    u8 finished = 1;
    u16 index;

    for (index = 0; index < length; ++index) {
        if (objects[index] != 0) {
            if (object_is_state_2(objects[index])) {
                func_08005B58(objects[index]);
                objects[index] = 0;
            } else {
                finished = 0;
            }
        }
    }
    return finished;
}
