#include "ffta.h"

void func_08124648(void);
void func_08125624(u32 selector);

u32 func_08122FCC(void *context, const u8 *script)
{
    if (script[1] == 0)
        func_08124648();
    else
        func_08125624(script[1]);
    return 0x114;
}
