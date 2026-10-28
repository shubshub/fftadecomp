# 0x0813B060: packed table selection

Target: complete [0x0813B060, 0x0813B0A8), **72 bytes / 33 instructions**.
Preserved candidate: **72-byte complete ELF symbol** with fixed
`agbcc -mthumb-interwork -O2`. Native matcher exits 1; source plausible;
11/33 instructions and 43/72 bytes identical.

The function scans 16 halfword table entries. Entries whose high byte matches
the selector store their table index into trailing output bytes at the low-byte
offset. A halfword match count is stored first and returned truncated to a byte.
The zero-length trailing array describes storage of unknown complete extent.

Remaining difference: address computation and register allocation. The target
keeps output/count/index in r3/r4/r2 and table/mask in r7/r6, forming output+2
inside the matching branch. The candidate keeps output/count/index in r6/r1/r3,
uses r12 for the table and r7 for the mask, and hoists output+2 into r4.
Consequent instruction ordering, branch displacement and literal load differ.

Bounded natural attempts: raw halfword output plus byte cast (64-byte symbol);
trailing-array structure with a halfword entry local (72 bytes, 46/72 bytes
identical); explicit low-byte cast (68 bytes); promoted word entry local
(current 72-byte candidate). No absent unused-load sites were identified.
No asm, volatile, pragmas, compiler flag changes or shared-file edits.

The unmatched src/report have been removed. Root owns lease release.
