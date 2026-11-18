#include "ffta.h"

extern u32 func_08002804(void);

u16 func_080D2EE8(void)
{
    return (s16)func_08002804() % 2000 + 1000;
}
