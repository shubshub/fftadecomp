# 0802B07C

Target: complete indexed Thumb body `0x0802B07C..0x0802B108`, 140 bytes / 58 reachable instructions.

The retained C compiles under fixed agbcc `-mthumb-interwork -O2` to a complete 140-byte symbol. The native matcher exits 1, reports source plausible and **NOT MATCHING - bytes differ**, and gives an aligned diff score of 51/58 instructions and 131/140 bytes. These are native alignment scores, not same-offset byte-equality claims. The retained emitted instruction stream has the same 58-instruction extent.

The function scrolls a halfword buffer using the named temporary buffer at `data_02003CB0`. Direction 0x80 copies the remaining rows upward and increments the halfword position at +0x1A; direction 0x40 copies them downward and decrements that position. Width and height are bytes at +0x15 and +0x16, and the buffer pointer is at +0xC. Both copy calls use the 21-bit BIOS count mask.

The remaining differences are register allocation for the narrowed total and row stride. The target places the total in r4, preserving it in r6, and the stride in r2, preserving it in r7. The compiler places the total in r2/r7 and the stride in r4/r6. Consequently, the upward subtraction is `subs r4, r2, r4` rather than `subs r4, r4, r2`, the downward subtraction is `subs r4, r7, r6` rather than `subs r4, r6, r7`, and the stride-shift operands differ. The branches, call targets, temporary-buffer binding, masks, and complete symbol length agree.

Natural attempts covered halfword versus word-sized dimensions/counts, shared versus branch-local copy counts, updating a remaining-count local, explicit source pointers, and count expressions supplied directly to the BIOS-copy calls. A halfword conversion of the doubled height reproduces the target's multiply ordering. Halfword total and stride retain the target-size 140-byte symbol; widened totals produced 128-byte symbols, and the initial reassociated product produced 124 bytes. Word-sized strides retained 140 bytes but introduced additional register differences. No assembly, volatile accesses, pragmas, altered flags, dead code, helpers, or shared-file changes were used.
