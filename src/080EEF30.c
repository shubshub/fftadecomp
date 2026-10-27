#include "ffta.h"

extern u16 func_08005BAC(void *task);

/* Complete [0x080EEF30, 0x080EEF4A): 26 bytes, 12 instructions. */
u8 func_080EEF30(void *task)
{
    if (func_08005BAC(task) == 0x102)
        return 1;
    return 0;
}
