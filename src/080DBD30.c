#include "ffta.h"

/* 0x080DBD30..0x080DBD48: 24 bytes / 10 instructions. */
struct ValueOwner;

extern void *func_080DD350(void *object);
extern u32 func_08099C04(const struct ValueOwner *owner, u8 *first, u8 *second);

u32 func_080DBD30(void *object, u8 *first, u8 *second)
{
    return func_08099C04(func_080DD350(object), first, second);
}
