#include "ffta.h"

void *func_08121DBC(void);
u8 func_080D3878(void *task);
void func_080D3864(void *task);
void func_08121DA8(void *task);

u32 func_08123994(void *context, const u8 *script)
{
    void *task = func_08121DBC();
    u32 result;

    if (!func_080D3878(task))
        result = 0x118;
    else {
        func_080D3864(task);
        func_08121DA8(0);
        result = 0x110;
    }
    return result;
}
