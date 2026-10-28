#include "ffta.h"

/* 0x080C7484..0x080C74B4: 48 bytes, 19 instructions, including a pool. */
extern u8 data_030028A0;
extern void *func_08022840(u32 size);
extern void func_080C62CC(void *state, void *first, void *second, u32 mode);

void *func_080C7484(void *first, void *second)
{
    void *state = func_08022840(0xB4);
    func_080C62CC(state, first, second, (data_030028A0 >> 3) & 1);
    return state;
}
