#include "ffta.h"

/* 0x080D7AB0..0x080D7ABA: 10 bytes, 4 instructions. */
extern void func_08005B58(void *task);

void func_080D7AB0(void *task)
{
    func_08005B58(task);
}
