#include "ffta.h"

typedef void (*BufferInitializer08009964)(void *destination, u32 size);

extern BufferInitializer08009964 const g_callbacks_0836D4B8[];
void func_080098C4(u8 outer_index, u8 *outer_flag);

void func_08009964(void)
{
    g_callbacks_0836D4B8[0]((void *)0x03000890, 32);
    func_08006ADC((Table *)0x03000880, 2, (u32)func_080098C4);
}
