#include "ffta.h"

/* FLASH512_V130 SwitchFlashBank. Unlock the command bus, select bank mode,
 * then send the requested bank number to offset zero. */
void func_0814189C(u8 bank)
{
    *(volatile u8 *)0x0E005555 = 0xAA;
    *(volatile u8 *)0x0E002AAA = 0x55;
    *(volatile u8 *)0x0E005555 = 0xB0;
    *(volatile u8 *)0x0E000000 = bank;
}
