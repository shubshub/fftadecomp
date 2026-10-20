#include "ffta.h"

void func_08021E68(u32 *flags)
{
    *flags = (*flags & 0xFFFDFF7F) | 0x00090000;
}
