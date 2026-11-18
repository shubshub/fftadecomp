#include "ffta.h"

typedef u8 (*FlashReader)(u8 *address);
extern void func_08141AB0(u16 *destination);

/* Read the FLASH512 device byte and maker byte in ID mode. */
u16 func_081418C0(void)
{
    u16 readBuffer[32];
    volatile u16 delay;
    FlashReader read;
    u16 id;

    func_08141AB0(readBuffer);
    read = (FlashReader)((u32)readBuffer + 1);
    *(volatile u8 *)0x0E005555 = 0xAA;
    *(volatile u8 *)0x0E002AAA = 0x55;
    *(volatile u8 *)0x0E005555 = 0x90;
    for (delay = 20000; delay != 0; delay--)
        ;

    id = read((u8 *)0x0E000001) << 8;
    id |= read((u8 *)0x0E000000);
    *(volatile u8 *)0x0E005555 = 0xAA;
    *(volatile u8 *)0x0E002AAA = 0x55;
    *(volatile u8 *)0x0E005555 = 0xF0;
    *(volatile u8 *)0x0E005555 = 0xF0;
    for (delay = 20000; delay != 0; delay--)
        ;

    return id;
}
