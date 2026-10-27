# 0802ECEC — Parked

Target: complete [0x0802ECEC, 0x0802ED88), 156 bytes / 70 reachable instructions.

The complete recovered behavior clears the selected-row mask, scans the nonzero halfword identifiers at state offset 0x3c34, and sets a row bit when the filter accepts that identifier. Filters 0x56 through 0xaa compare the identifier with filter - 0x55; filters 0xab through 0xb0 compare the 16-byte table entry's category byte with filter - 0xaa; other filters accept all nonzero identifiers.

The preserved, tested direct reconstruction compiles to 146 bytes under fixed agbcc -mthumb-interwork -O2. The unchanged native matcher returns exit 1 at the short-symbol extent gate (146 < 156), before plausibility and full comparison. No plausibility or match credit is claimed for this candidate.

Compiler assembly inspection identifies the remaining difference: the target saves r8 and r9, keeps the first narrowed range value in r8 and the category-table base in r9, and hoists the bit constant 1 into r6 before the loop. The candidate saves only r8, keeps the range value in r7 and table base in r8, and materializes 1 inside the mask update. In the identifier branch it reuses the initial halfword load through a register copy; the target reloads that halfword after its range test. These differences change register allocation, frame instructions, loop setup, and total symbol size. All recovered semantic branches are present in the preserved C.

Three bounded reconstructions were tested: direct predicate and compound mask update (preserved, 146-byte extent refusal); a semantic inline predicate with explicit mask/loaded-flags locals (156 bytes, source plausible, native exit 1 with substantial control-flow/register differences); and a semantic inline bit setter with the original predicate (146-byte extent refusal). No compiler flags, gates, or source steering were introduced.

Private native output and the nonmatching predicate-helper report remain in the address scratch directory. That report belongs to the predicate-helper attempt, not the preserved direct candidate. Unmatched active source and report were removed. This directory contains only the recovered C and this diagnosis.
