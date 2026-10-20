#include "ffta.h"

void func_08021DE4(u32 *flags, u16 clear, u16 set)
{
    *flags = (*flags & ~clear) | set;
}
