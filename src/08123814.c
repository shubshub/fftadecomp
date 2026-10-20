#include "ffta.h"

void func_081247B4(u32 selector);
void func_08124850(u32 selector);

u32 func_08123814(void *context, const u8 *script)
{
    if (script[2]) {
        func_081247B4(script[1]);
    } else {
        func_08124850(script[1]);
    }
    return 0x110;
}
