#include "ffta.h"

void func_08124480(u32 first, u32 second, u32 third, u32 fourth, u32 fifth);

u32 func_08122F8C(void *context, const u8 *script)
{
    u32 first = script[1];
    u32 second = script[2] & 0xF;
    u32 third = script[2] >> 4;
    u32 fourth = script[3];
    u32 fifth = script[4] & 0xF;

    func_08124480(first, second, third, fourth, fifth);
    return 0x110;
}
