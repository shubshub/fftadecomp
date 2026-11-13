#include "ffta.h"

// Target [0x0813DE38, 0x0813DF5C), 292 bytes:
// f0b557464e464546e0b486b088460e990f9c109d119e0006000e00901206170e1b061b0e
// 01930906090e89462406240e2d062d0e02953606360e0396dd1b2d062d0e484600028246
// 210205910e1c029a4946501a0002291c04f012fc0004000c0490039a141b2402201c291c
// 04f008fc0004020c0025bd420ad2494605980143680040440180681c0006050ebd42f7d3
// 3d1c01998d4221d21f4884460499080400148146100407146c00444433041b14191c6246
// 11405246100402140016014321804a441204120c9246db191b041e0c681c0006050e0198
// 8542e5d3019d9f2d0bd803990c02029a1443680040440480681c0006050e9f2df7d9084a
// 084b00984146c2f605ff06b038bc9846a146aa46f0bc01bc0047000000ffffff52000004
// 01004020

extern void func_08000D48(u8 channel, const void *source, void *destination, u32 control);

void func_0813DE38(u8 channel, u16 *buffer, u8 start, u8 end,
                   u8 eva_from, u8 evb_from, u8 eva_to, u8 evb_to)
{
    u8 row;
    u8 span;
    s16 eva;
    s16 evb;
    s16 eva_step;
    s16 evb_step;

    span = end - start;
    eva = eva_from << 8;
    evb = evb_from << 8;
    eva_step = ((eva_to - eva_from) << 8) / span;
    evb_step = ((evb_to - evb_from) << 8) / span;

    for (row = 0; row < start; row++)
        buffer[row] = eva_from | (evb_from << 8);
    for (row = start; row < end; row++) {
        buffer[row] = (evb & ~0xFF) | (eva >> 8);
        eva += eva_step;
        evb += evb_step;
    }
    for (row = end; row < 160; row++)
        buffer[row] = eva_to | (evb_to << 8);
    func_08000D48(channel, buffer, (void *)0x04000052, 0x20400001);
}
