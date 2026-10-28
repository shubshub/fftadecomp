#include "ffta.h"

typedef void (*ObjectInitializer080A87DC)(void *object, u32 size);

extern ObjectInitializer080A87DC const g_callbacks_0836D4B8[];
extern void func_08022854(void *object);

/* 0x080A87DC: initialize the complete 0x2C4-byte object, then its contents. */
void func_080A87DC(void *object)
{
    g_callbacks_0836D4B8[0](object, 0x2C4);
    func_08022854(object);
}
