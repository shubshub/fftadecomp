/* func_0801121C - 0x0801121C, 44 bytes (0x0801121C .. 0x08011248)
 *
 *   push {r4, lr}
 *   lsls r1, r1, #16      (u16) parameter
 *   adds r2, r0, #0       item
 *   lsrs r3, r1, #16      the (u16) parameter value
 *   cmp r1, #0
 *   bne  0x08011234       flag != 0 -> set the bit
 *   ldrh r1, [r2, #0x14]
 *   ldr  r0, [pc, #4]     0x0000FFF7
 *   ands r0, r1
 *   b    0x0801123E
 *   .word 0x0000FFF7      literal pool
 *   ldrh r1, [r2, #0x14]  0x08011234
 *   movs r4, #0x80
 *   lsls r4, r4, #4       0x0800
 *   adds r0, r4, #0
 *   orrs r0, r1
 *   strh r0, [r2, #0x14]  0x0801123E
 *   strh r3, [r2, #0x16]
 *   pop {r4}
 *   pop {r0}
 *   bx  r0
 */

#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u16 field_14;
    u16 field_16;
} Struct0801121C;

void func_0801121C(Struct0801121C *item, u16 flag)
{
    if (flag == 0)
        item->field_14 &= 0xFFF7;
    else
        item->field_14 |= 0x800;

    item->field_16 = flag;
}
