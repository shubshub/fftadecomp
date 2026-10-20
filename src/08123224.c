#include "ffta.h"

void func_08125444(const u8 *arguments);

u32 func_08123224(void *context, const u8 *script)
{
    func_08125444(script + 1);
    return 0x110;
}
