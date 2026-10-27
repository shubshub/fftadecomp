# 0800C2FC: record cleanup loop reconstruction

Target: [0x0800C2FC, 0x0800C344), 72 bytes and 30 reachable instructions.

The full fixed-toolchain attempt reaches native complete-symbol and ordinary
Thumb-call CFG verification, then fails byte comparison: native exit 1,
66/72 same-offset bytes and 25/30 identical instructions. Source plausibility
passes. No exact match or match credit is claimed.

The target calls func_0800C1C8 for indices 0 and 1 using a u16 loop counter
narrowed to u8 at the call. A second u16 loop scans two 40-byte records at
0x02009000. Each nonnull allocation at record offset 0 is freed through
func_08007170 using the allocator at 0x02008FF8. The existing matched
0800C1C8 source confirms the allocation field, stride, allocator and cleanup
operation. The preserved static inline helper groups that actual allocation
cleanup; the unchanged native gate accepts the emitted target-only function.

Remaining difference: agbcc hoists the constant record-table address into r5
before the second loop. The ROM loads it into r1 inside the loop, after the
index-times-40 computation. Consequently the candidate saves/restores r5,
uses r5 for the table-base addition, and has a different loop-back displacement
and PC-relative load encoding. Both complete function symbols are 72 bytes;
the first loop, conditional release, allocator load, literal values and return
behavior otherwise agree.

Three natural forms were tested: direct repeated field access, a local
allocation pointer, and the semantic static inline release helper preserved
here. All produced the same complete 72-byte candidate and remaining gap.
No compiler options, artificial volatile, assembly, forced inlining or
manufactured expressions were used. Fixed flags: -mthumb-interwork -O2.

The last native report is retained outside this pair at
../../../0800C2FC/last-native-report.md relative to this README's directory
(the private batch address scratch directory). Unmatched active source and
report were removed after preserving this complete tested candidate.
