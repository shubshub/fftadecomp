#include "ffta.h"

typedef struct Object08092288 {
    u8 unknown_00[0x58];
    struct Object08092288 *child;
} Object08092288;

extern void func_08022854(void *object);

/* 0x08092288..0x080922A2: 26 bytes, 11 instructions. */
void func_08092288(Object08092288 *object)
{
    if (object->child) {
        func_08022854(object->child);
    }
    func_08022854(object);
}
