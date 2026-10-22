#include "ffta.h"

void func_080088D8(void);
void func_08008938(void);
u8 func_08008954(void);

/* Target: 0x08008880, 88 bytes including internal alignment and literal pool. */
u8 func_08008880(void)
{
    u16 **active = (u16 **)0x02009188;

    if (*active == 0)
        return 1;

    switch (**active) {
    case 0:
        func_080088D8();
        **active = 1;
        break;
    case 1:
        if (func_08008954())
            **active = 2;
        break;
    case 2:
        func_08008938();
        return 1;
    }

    return 0;
}
