/* func_08115ACC - 0x08115ACC..0x08115AE2, 22 bytes
 * target: 00b5c7f7d5fc0020012100220023c6f7fbf901bc0047
 */

#include "ffta.h"

extern void *func_080DD47C(void *object);
extern void func_080DBED4(u8 selector, u8 flag, void *skip, void *arg);

void func_08115ACC(void *object)
{
    func_080DD47C(object);
    func_080DBED4(0, 1, 0, 0);
}
