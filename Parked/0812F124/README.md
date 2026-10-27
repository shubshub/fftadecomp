# 0812F124

Target: complete [0812F124, 0812F152), 46 bytes / 18 reachable instructions.
The preserved candidate also has a complete 46-byte ELF symbol. Native matcher
exit 1: source plausible, direct-Thumb-call CFG accepted, 44/46 bytes and
16/18 instructions identical. No match credit.

The function forwards its incoming object pointer to 080C9428. A nonnegative
index selects a 16-byte record at global state offset 2E78; a nonzero first
word rejects the record. The result is its address or null.

Only the successful-return address calculation differs. ROM uses
`adds r0, r2, r3; adds r0, r1, r0` at 0812F13E/0812F140, where R2 is the
global base, R3 is 2E78 and R1 is index * 16. The candidate uses
`adds r0, r1, r3; adds r0, r0, r2`. The calculations are equivalent.

Tested natural forms: a typed global record array (46 bytes, different branch
and address allocation); byte-offset access with a nested validity guard
(44/46 bytes, 17/18 instructions, but base LDR and index shift swapped);
explicit byte-pointer arithmetic (same result); named base and byte offset
(preserved allocation); and a typed record-array return (same preserved bytes).
No forced registers, asm, artificial volatile, compiler flags or padding were
used. The last native report is saved in address scratch as last-native-report.md.
