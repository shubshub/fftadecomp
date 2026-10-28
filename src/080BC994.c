#include "ffta.h"

typedef void (*BufferInitializer)(void *destination, u32 size);

extern BufferInitializer const g_callbacks_0836D4B8[];
extern void func_08022854(u8 *object);

/* 080BC994..080BC9B8: 36 bytes. */
void func_080BC994(u8 *object)
{
    g_callbacks_0836D4B8[0](object, 456);
    func_08022854(object);
}
