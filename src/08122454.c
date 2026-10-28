#include "ffta.h"

extern void *func_08121D0C(s32 index);
extern void func_08121D20(s32 index, void *object);

/* Target: [0x08122454, 0x08122482), 46 bytes.
 * 30b5051c0024201cfff756fc002807d0a84205d1201c0021fff758fc012003e001340f2c
 * efdd002030bc02bc0847
 */
u32 func_08122454(void *object)
{
    s32 i;

    for (i = 0; i < 16; i++) {
        void *entry = func_08121D0C(i);

        if (entry != 0 && entry == object) {
            func_08121D20(i, 0);
            return 1;
        }
    }
    return 0;
}
