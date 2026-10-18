/* func_0800BC28 - 0x0800BC28, 30 bytes  (PARKED: compiles to 28, see README.md)
 *
 * Reads the x/y s16 pair at +0x18/+0x1A of one 40-byte record of the table at
 * 0x02009000.  The index is masked to a byte (lsl/lsr #24) before it is scaled
 * by the 40-byte stride, exactly as the ROM does; ffta.h's Rec40 is only 28
 * bytes long, so the stride is spelled out rather than taken from sizeof.
 *
 * This reproduces every body instruction of the ROM and nothing else differs
 * in meaning, but the literal base costs two bytes: agbcc materialises a
 * literal address at its point of use, i.e. after the index scaling, by which
 * time r0 (the masked index) is dead, so the base lands in r0 and no
 * callee-saved register is needed - no push {r4, lr}, and `bx lr` instead of
 * the interworking epilogue.
 *
 *   compiled  0600 0e00 0083 181b 00db 4803 181b 8b18 8008 8b58 8010 4770
 *   target    10b5 0600 0e00 4c06 0083 181b 00db 191b 8b18 8008 5b58 8010
 *             10bc 01bc 4700
 */

#include "ffta.h"

void func_0800BC28(u32 index, s16 *a, s16 *b) {
    Rec40 *r = (Rec40 *)((u8 *)0x02009000 + (u8)index * 40);
    *a = r->x;
    *b = r->y;
}