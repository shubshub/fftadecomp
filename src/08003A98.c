#include "ffta.h"

// Complete target [0x08003A98, 0x08003B1C): 132 bytes, 47 instructions.
// 70b5464640b482b0164b1a8800251d80154e164ce08880210843002188462843
// e0803080124908801a80424600921149114c6846221c3df1cdfe4046019001a8
// 0e49221c3df1c6fe0d4801214172922252008018017002b008bc984670bc01bc
// 0047000008020004500e0003a00e000300020004700800030100000580270003
// a0280003
// Enables interrupt bit 7 (serial) with IME held off, then clears two
// words and arms the serial state at 0x030028A0.

typedef struct {
    u8 unknown_000[9];
    u8 field_09;
    u8 unknown_00A[0x11A];
    u8 status;
} SerialState08003A98;

typedef struct {
    u8 unknown_00[6];
    u16 interrupt_mask;
} InterruptState08003A98;

extern SerialState08003A98 data_030028A0;
extern InterruptState08003A98 data_03000EA0;
extern u16 data_03000E50;
extern u32 data_03000870;
extern u32 data_03002780;
extern void func_0814186C(const void *source, void *destination, u32 control);

void func_08003A98(void)
{
    u32 fill_first;
    u32 fill_second;
    u16 ime;
    u16 *shadow;

    // plausible: REG_IME is hardware; the saved value is read from the register.
    ime = *(volatile u16 *)0x04000208;
    // plausible: REG_IME is hardware; the zero store must reach the register.
    *(volatile u16 *)0x04000208 = 0;
    // The ROM takes the shadow's address (ldr r6, =0x03000E50 at 0x08003AA8)
    // before the mask update at 0x08003AAA and holds it in r6 to the store at
    // 0x08003ABA, as src/08003888.c takes its pointers before its stores.
    shadow = &data_03000E50;
    data_03000EA0.interrupt_mask |= 0x80;
    *shadow = data_03000EA0.interrupt_mask;
    *(u16 *)0x04000200 = *shadow;
    // plausible: REG_IME is hardware; restoring it re-enables interrupts.
    *(volatile u16 *)0x04000208 = ime;

    fill_first = 0;
    func_0814186C(&fill_first, &data_03000870, 0x05000001);
    fill_second = 0;
    func_0814186C(&fill_second, &data_03002780, 0x05000001);
    data_030028A0.field_09 = 1;
    data_030028A0.status = 1;
}
