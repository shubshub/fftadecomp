#include "ffta.h"

extern void *func_08022840(u32 size);
extern void func_080BDBAC(void *destination);

/* Target bytes (28):
 * 10 b5 05 48 64 f7 9e fe 04 1c 00 f0 51 f8 20 1c
 * 10 bc 02 bc 08 47 00 00 04 45 00 00
 */
void *func_080BDAFC(void)
{
    void *object = func_08022840(0x4504);

    func_080BDBAC(object);
    return object;
}
