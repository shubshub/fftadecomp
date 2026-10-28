#include "ffta.h"

typedef void (*ObjectInitializer080B7E7C)(void *object, u32 size);

extern ObjectInitializer080B7E7C const g_callbacks_0836D4B8[];
extern void func_08022854(void *object);

/* 0x080B7E7C: initialize the complete 0x1160-byte object, then its contents. */
void func_080B7E7C(void *object)
{
    g_callbacks_0836D4B8[0](object, 0x1160);
    func_08022854(object);
}
