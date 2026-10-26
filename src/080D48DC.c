#include "ffta.h"

extern u32 func_08005BB0(void *object);
extern void func_08005B58(void *object);

static inline u8 object_finished(void *object)
{
    if (func_08005BB0(object))
        return 1;
    return 0;
}

u8 func_080D48DC(void **objects, u16 count)
{
    u8 complete = 1;
    u16 i;

    for (i = 0; i < count; i++) {
        if (objects[i]) {
            if (object_finished(objects[i])) {
                func_08005B58(objects[i]);
                objects[i] = 0;
            } else {
                complete = 0;
            }
        }
    }
    return complete;
}
