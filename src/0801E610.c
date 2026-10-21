/* func_0801E610 - 0x0801E610, 12 bytes of code (6 instructions) + one 4-byte
 * literal pool word at 0x0801E61C.
 *
 *   024b  ldr  r3, [pc, #8]   ; r3 = 0x02007F40 (pool)
 *   1a78  ldrb r2, [r3]        ; r2 = byte at 0x02007F40
 *   0270  strb r2, [r0]        ; *a = that byte
 *   5878  ldrb r0, [r3, #1]    ; r0 = byte at 0x02007F41
 *   0870  strb r0, [r1]        ; *b = that byte
 *   7047  bx   lr
 *
 * The two arguments are byte pointers: every caller passes the address of a
 * byte slot and reads the byte back out of it afterwards.
 */

#include "ffta.h"

void func_0801E610(u8 *a, u8 *b) {
    u8 *source = (u8 *)0x02007F40;

    *a = source[0];
    *b = source[1];
}
