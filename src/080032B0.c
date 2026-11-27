// func_080032B0 - 0x080032B0, 72 bytes (0x080032B0 .. 0x080032F8), 27 instructions.
//
// target  10b50448044c0268201c50213ef1c6ff05e00000b8d4360840090003fee70948
//         60210180c18b80225200c283c18b438b4183c18dc285c18d428d418510bc01bc
//         0047000040090003
//
// Clears the 0x50-byte display register shadow at 0x03000940 through the
// ROM callback table, then sets DISPCNT to 0x60 and the BG2/BG3 affine
// PA and PC terms to 0x100 (1.0).
//
// The `b .` at 0x080032CC never runs. The `b` at 0x080032C0 jumps over it,
// and over the literal pool at 0x080032C4 (0x0836D4B8, the callback table)
// and 0x080032C8 (0x03000940), to 0x080032CE, and no other branch reaches it.
// It is the loop of `if (display >> 16) for (;;);`, a failed-check trap on a
// u16 member whose test is always false: agbcc proved that only during
// combine, after the last jump pass that would have removed the loop, so the
// test went and the loop stayed.

#include "control_flags.h"

typedef void (*BufferInitializer080032B0)(void *destination, u32 size);

extern BufferInitializer080032B0 const g_callbacks_0836D4B8[];

void func_080032B0(void)
{
    g_callbacks_0836D4B8[0](&g_control_flags_03000940, sizeof(g_control_flags_03000940));
    if (g_control_flags_03000940.display >> 16)
        for (;;)
            ;
    g_control_flags_03000940.display = 0x60;
    g_control_flags_03000940.bg2pa = g_control_flags_03000940.bg2pc = 0x100;
    g_control_flags_03000940.bg3pa = g_control_flags_03000940.bg3pc = 0x100;
}
