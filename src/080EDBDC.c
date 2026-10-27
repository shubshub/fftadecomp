#include "ffta.h"

/* 0x080EDBDC..0x080EDC08: complete 44-byte object completion wrapper. */
extern u32 func_08005BB0(const void *object);
extern void func_08005B58(void *object);

static inline u8 object_finished(const void *object)
{
    if (func_08005BB0(object))
        return 1;
    return 0;
}

void *func_080EDBDC(void *object)
{
    if (object && object_finished(object)) {
        func_08005B58(object);
        return 0;
    }
    return object;
}
