#include "ffta.h"

/* 0x080161BC..0x080161D4: 24 bytes / 10 instructions. */
extern u16 func_08014778(const u8 *text);
extern u16 func_08013BC0(u16 value, u8 bits);

u16 func_080161BC(const u8 *text)
{
    return func_08013BC0(func_08014778(text), 8) >> 3;
}
