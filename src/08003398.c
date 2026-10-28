#include "ffta.h"

/* plausible: DISPSTAT at 0x04000004 is hardware; bit 0 changes during VBlank. */
#define DISPSTAT (*(volatile u16 *)0x04000004)

/* 0x08003398..0x080033C8: 48 bytes. Wait for the next VBlank. */
void func_08003398(void)
{
    while (DISPSTAT & 1)
        ;
    while (!(DISPSTAT & 1))
        ;
}
