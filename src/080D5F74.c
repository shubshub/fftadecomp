#include "ffta.h"

extern void func_08011428(void *object);

/* Complete [0x080D5F74, 0x080D5FA4): 48 bytes, 23 instructions. */
void func_080D5F74(void **objects, u16 count)
{
    u16 index;

    for (index = 0; index < count; index++) {
        if (objects[index] != 0) {
            func_08011428(objects[index]);
            objects[index] = 0;
        }
    }
}
