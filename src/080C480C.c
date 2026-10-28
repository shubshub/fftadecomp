#include "ffta.h"

typedef void (*BufferInitializer080C480C)(void *destination, u32 size);

extern BufferInitializer080C480C const g_callbacks_0836D4B8[];
extern void func_08022854(u8 *object);

/* Complete target [0x080C480C, 0x080C4830): 36 bytes, 12 instructions. */
void func_080C480C(u8 *object)
{
    g_callbacks_0836D4B8[0](object, 0x5684);
    func_08022854(object);
}
