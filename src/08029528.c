#include "ffta.h"

extern void func_08025688(u32 command, u32 first, u32 second);

/* 08029528..08029542: 26 bytes. */
void func_08029528(u16 command)
{
    func_08025688(command | 0x4000, 0, 0);
}
