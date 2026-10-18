/* func_08003A40 - 0x08003A40, 40 bytes (36 + 4-byte literal pool)
 *
 * Target bytes:
 *   push {r7, lr} / sub sp, #8 / mov r7, sp / str r0, [r7]
 *   ldr r0, [pc, #0x1c] / ldr r1, [r7] / adds r2, r1, #0 / lsls r1, r2, #2
 *   adds r0, r0, r1 / ldr r1, [r0] / str r1, [r7, #4] / ldr r1, [r7, #4]
 *   adds r0, r1, #0 / adds r0, #8 / movs r1, #0 / str r1, [r0]
 *   add sp, #8 / pop {r7} / pop {r0} / bx r0
 *   pool 0836d480
 */

#include "ffta.h"

void func_08003A40(int index) {
    u32 *table = (u32 *)0x0836D480;
    u8 *entry = (u8 *)table[index];
    *(u32 *)(entry + 8) = 0;
}