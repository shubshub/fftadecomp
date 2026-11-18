#include "ffta.h"

extern void func_08031708(u8 value);

/* The second callback installed at 080348FC sets the state byte to 0xFE. */
void func_080318DC(void)
{
    func_08031708(0xFE);
}
