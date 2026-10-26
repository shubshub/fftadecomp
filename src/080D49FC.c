#include "ffta.h"

extern void func_080D4A28(u8 first, u8 second, u16 third, s16 fourth, s16 fifth, u32 mode);

void func_080D49FC(u8 first, u8 second, u16 third, s16 fourth, s16 fifth)
{
    func_080D4A28(first, second, third, fourth, fifth, 0);
}
