#include "ffta.h"

/* 0x080C7240..0x080C7260: 32 bytes. */
typedef void (*BufferInitializer080C7240)(void *destination, u32 size);

extern u8 data_02015738[];
extern BufferInitializer080C7240 const g_callbacks_0836D4B8[];
extern void func_080C7214(void);

void func_080C7240(void)
{
    u8 *state = data_02015738;

    g_callbacks_0836D4B8[0](state, 248);
    func_080C7214();
}
