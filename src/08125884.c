#include "ffta.h"

extern void *func_08121D0C(u32 index);
extern void func_08121BB8(void *task);
extern void func_08121D20(u32 index, void *task);

void func_08125884(void)
{
    s32 index;

    for (index = 0; index < 16; index++) {
        void *task = func_08121D0C(index);

        if (task) {
            func_08121BB8(task);
            func_08121D20(index, 0);
        }
    }
}
