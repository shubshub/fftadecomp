#include "ffta.h"

/* Complete [0x081307C8, 0x081307F4): 44 bytes, 21 instructions. */
extern u32 func_0812FE38(u32 first, u32 second, u16 third, u16 fourth,
                        u16 fifth, u8 sixth, u32 enabled);

u32 func_081307C8(u32 first, u32 second, u16 third, u16 fourth,
                  u16 fifth, u8 sixth)
{
    return func_0812FE38(first, second, third, fourth, fifth, sixth, 1);
}
