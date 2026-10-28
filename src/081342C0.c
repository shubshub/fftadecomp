#include "ffta.h"

extern u32 func_08133F70(u32 first, u32 second, u32 mode);

u32 func_081342C0(u32 first, u32 second)
{
    return func_08133F70(first, second, 1);
}
