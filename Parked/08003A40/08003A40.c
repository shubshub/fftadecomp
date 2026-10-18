/* func_08003A40 - 0x08003A40, 44 bytes (40 of code + a 4-byte literal pool at
 * 0x08003A68)
 *
 * MATCHED byte-for-byte with: agbcc -mthumb-interwork -O0
 *   target  80b5 82b0 6f46 3860 0748 3968 0a1c 9100 4018 0168 7960 7968 081c
 *           0830 0021 0160 02b0 80bc 01bc 0047
 *   pool    0836d480
 *
 * Zeroes the third word of the entry the pointer table at 0x0836D480 selects.
 * The ROM bytes are the table itself: four consecutive 32-bit pointers
 * (0x040000B0, 0x040000BC, 0x040000C8, 0x040000D4), so the table is modelled
 * as an array of slots inside a struct at that fixed address.
 *
 * NOTE ON THE OPTIMISATION LEVEL: this function is NOT built at -O2.  Every
 * plain table-lookup shape folds to 18 bytes at -O1/-O2/-O3/-Os:
 *
 *   lsls r0,r0,#2 / ldr r1,.L3 / add r0,r0,r1 / ldr r1,[r0] / mov r0,#0 /
 *   str r0,[r1,#8] / bx lr
 *
 * The ROM instead keeps a frame (`push {r7,lr}` / `sub sp,#8` / `mov r7,sp`),
 * spills the argument to [r7] and the entry pointer to [r7+4], and reloads
 * both.  In agbcc `frame_pointer_needed` is set at the start of reload1 only
 * when an elimination to sp is refused (reload1.c: `init_elim_table` /
 * `eliminate_impossible_registers`), i.e. when flag_omit_frame_pointer is off
 * (-fno-omit-frame-pointer, which breaks all 45 already matched sources) or
 * when sp is written with something other than a constant (alloca).  Plain
 * -O2 code simply never emits `mov r7, sp`; -O0 does, unconditionally, which
 * is exactly what the ROM shows - including in its neighbours 0x08000670,
 * 0x080006D0, 0x08000718, 0x08000788 and 0x08003A08, the only five other
 * functions in the ROM that use r7 as a frame pointer.
 *
 * Two more -O0 artefacts are reproduced by the source below: the literal pool
 * is loaded before the index is scaled (`ldr r0,[pc, #0x1c]` first), which
 * needs the table address to be materialised as the base of the COMPONENT_REF
 * rather than folded into a pointer PLUS, and the entry pointer is written to
 * the frame and read back because -O0 keeps every local in memory.
 *
 * The struct is what fixes the evaluation order: `table[index]` on a bare
 * pointer is a PLUS_EXPR, which expr.c canonicalises to `index * 4 + const`
 * (the index is expanded first, and the constant materialised last), whereas
 * the component reference `((EntryTable *)0x0836D480)->slots[index]` expands
 * the base first (`force_reg` on the constant) and then the scaled index.
 *
 * match.py cannot confirm this one: its leaf verifier rejects any instruction
 * that writes sp outside push/pop ("unsupported stack-pointer adjustment"),
 * so no function with a stack frame can be checked by it at all - every source
 * in src/ so far is frameless.  The bytes above were verified by compiling
 * with agbcc -mthumb-interwork -O0, assembling and diffing the .text section
 * against baserom.bin 0x08003A40..0x08003A6C: 44 of 44 bytes identical.
 */

#include "ffta.h"

typedef struct {
    u32 *slots[4];
} EntryTable;

void func_08003A40(int index) {
    u32 *entry = ((EntryTable *)0x0836D480)->slots[index];
    *(u32 *)((u8 *)entry + 8) = 0;
}