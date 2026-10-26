# 080B4DE8 — Parked

Target: unchanged indexed range 0x080B4DE8..0x080B4FF8, 528 bytes / 255 reachable instructions.

The preserved complete natural C candidate passed the native source-plausibility check but did not match. Fresh default native verification exited 1 with a 530-byte complete ELF symbol: 214/251 aligned instructions and 487/530 aligned bytes. The extended comparison includes two bytes beyond the indexed target; within the actual 528-byte indexed extent, 302 bytes match at the same offsets. No exact-match credit is claimed.

The collection, eligibility filtering, selected-index recording, ordering, source-to-last movement, coordinate finalization, and per-entry status loops are all implemented. The remaining gap is compiler control-flow and register allocation: the filtered-entry join uses cmp/beq/move/unconditional-branch instead of the target move/cmp/bne/unconditional-branch layout. In ordering, the candidate retains the signed count in SL and spills the last-index bound, while the target retains the bound in SL, copies the count through R5 into R2, and keeps the entry base in R3. The candidate therefore has an additional count-register move and different spill/register choices through the ordering loop, with following code shifted by two bytes.

Bounded natural reconstructions covered indexed versus countdown collection, advancing the point pointer with the index, separate collection/order/search indices, direct versus cached entry-array access, an explicit last index, a signed-byte count snapshot, and reuse of the completed point count with conditional eligible-entry selection. The preserved candidate is the best tested complete form. No assembly, pragmas, volatile objects, dead code, compiler-flag changes, shared edits, or register-steering constructs were used.

Verification used the approved ROM and the shared native match.py with fixed agbcc -mthumb-interwork -O2, PYTHONDONTWRITEBYTECODE=1, TMPDIR=/home/user/tmp and the approved ARM toolchain PATH. Full target disassembly, final native output, and last-native-report.md remain in the private address scratch directory. The unmatched active source/report were removed.
