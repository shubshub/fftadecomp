/* func_0801115C - 0x0801115C, 36 bytes (0x0801115C .. 0x08011180)
 *
 *   push {lr}
 *   adds r2, r0, #0        item
 *   lsls r1, r1, #24       (u8) flag
 *   cmp r1, #0
 *   beq  0x08011174        flag == 0 -> set the bit
 *   ldrh r1, [r2, #0x14]
 *   ldr  r0, [pc, #4]      0x0000FFFE
 *   ands r0, r1
 *   b    0x0801117A
 *   .word 0x0000FFFE       literal pool
 *   ldrh r1, [r2, #0x14]   0x08011174
 *   movs r0, #1
 *   orrs r0, r1
 *   strh r0, [r2, #0x14]   0x0801117A
 *   pop {r0}
 *   bx  r0
 */

#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u16 field_14;
} Struct0801115C;

void func_0801115C(Struct0801115C *item, u8 flag)
{
    if (flag)
        item->field_14 &= 0xfffe;
    else
        item->field_14 |= 1;
}
