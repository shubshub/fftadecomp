/* func_0804C5F8 - 0x0804C5F8, 110 bytes
 *
 * Builds one 28-byte table entry.  The destination is a byte pointer plus
 * index * 28 (the same scale as func_0804C788, spelled the same way: shift,
 * subtract, shift).  Two fields come out of a table lookup: the pointer at +0x00
 * is the row plus 2, and the byte at +0x0E is the low byte of a u16 at
 * row + *row.  The rest are arguments, stored in the order the instructions
 * do, which is not the order they appear in the signature.
 *
 * Arguments, as the register allocator sees them:
 *   r0 base      r1 index   r2 kind (shifted >> 14)   r3 -> +0x10
 *   +5 -> +0x11  +6 -> +0x0A (as u16)  +7 -> +0x13  +8 -> +0x18
 *   +9 table row pointer  +10 -> +0x16
 *
 *   target  f0b5 5746 4e46 4546 e0b4 089c a046 099e 0a9c a246 0b9f 0c9d
 *           0d9c a146 0904 090c 1204 3606 360e 920b aa18 1468 ca00 521a 9200
 *           1218 2819 0088 0021 9073 0234 2d19 1560 d173 1181 0120 5073
 *           5681 1374 4046 5074 0620 1073 5446 d474 9761 4846 d082 38bc
 *           9846 a146 aa46 f0bc 01bc 0047
 */

#include "ffta.h"

void func_0804C5F8(Entry *base, u16 index, u32 kind, u8 a4,
                   u8 a5, u8 a6, u8 a7, u32 a8, u8 *row, u16 a10) {
    u16 sel = kind;
    u8 *r = row + (sel >> 14);
    u32 head = *(u32 *)r;
    Entry *e = (Entry *)((u8 *)base + index * 28);
    e->field_0e = *(u16 *)(row + head);
    e->field_00 = (u32)(row + (head + 2));
    e->field_0f = 0;
    e->field_08 = 0;
    e->field_0d = 1;
    e->field_0a = a6;
    e->field_10 = a4;
    e->field_11 = a5;
    e->field_0c = 6;
    e->field_13 = a7;
    e->field_18 = a8;
    e->field_16 = a10;
}