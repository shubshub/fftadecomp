#include "ffta.h"

typedef void (*BufferInitializer080A8968)(void *destination, u32 size);

extern void *func_08022840(u32 size);
extern BufferInitializer080A8968 const g_callbacks_0836D4B8[];

/* Complete [0x080A8968, 0x080A8990): 40 bytes, 15 instructions. */
void *func_080A8968(void *context)
{
    void **state = func_08022840(0x50);

    g_callbacks_0836D4B8[0](state, 0x50);
    *state = context;
    return state;
}
