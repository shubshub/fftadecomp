#include "ffta.h"

extern void *data_0201C3C8;
extern void *func_08007138(void *owner, u32 bytes);

void *func_08137AEC(u32 bytes)
{
    return func_08007138(data_0201C3C8, bytes);
}
