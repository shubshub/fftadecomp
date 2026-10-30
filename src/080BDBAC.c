/* Target bytes (24):
 * 00 b5 03 4a 03 49 12 68 84 f0 4a fb 01 bc 00 47
 * b8 d4 36 08 04 45 00 00
 */
#include "ffta.h"

typedef void (*BufferInitializer)(void *destination, u32 size);

extern BufferInitializer const g_callbacks_0836D4B8[];
extern void func_0814224C(void *destination, u32 size,
                          BufferInitializer callback);

void func_080BDBAC(void *destination)
{
    BufferInitializer const *callbacks = g_callbacks_0836D4B8;

    func_0814224C(destination, 0x4504, callbacks[0]);
}
