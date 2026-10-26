# 08020BA0 — bounded natural C attempt

Complete indexed target: `[0x08020BA0, 0x08020DA0)`, 512 bytes and 242 reachable instructions. The full four-request queue body, both DMA transfer modes, completion callback and pointer/progress updates are retained.

The final native matcher run exits 1 with **plausible C**, a complete 512-byte ELF function, **488/512 identical bytes** and **222/242 identical instructions**, using fixed `agbcc -mthumb-interwork -O2`. Its source-bound native report is retained privately as `last-native-report.md`.

Remaining differences:

- The running transferred-byte count occupies `r8`; the target uses `sb`. This changes its initialization, copies into `sl`, restoration after a transfer and final return.
- In the row-transfer setup, the candidate initially compares the row index with the narrowed row count in `r0`, then moves that count to `r8` after the zero-row branch. The target places the count in `r8` before the initial comparison. The associated setup instructions and literal-load displacement differ.
- Tail temporaries differ: the size comparison uses `r3` instead of `r4`, the row-count reload uses `r4` instead of `r6`, and the next-index reload uses `r6` instead of `r1`.

Natural forms tried included direct versus captured DMA operands, conditional chunk selection, a 16-bit row width, narrow versus promoted row-count locals, direct row-count narrowing at the loop condition, and local declaration/initialization scopes. A const-qualified DMA pointer changed the function to 518 bytes; widening the row-count local changed register allocation without improving the match. No assembler, fixed registers, optimization changes, RAM qualification or artificial operations were introduced.

Only the genuine DMA3 MMIO pointee at `0x040000D4` is qualified for hardware access, with adjacent `plausible:` explanations. The original toolkit rejected that documented exception; root corrected its implementation, and the final native run accepts this source as plausible. That checker issue is resolved and is not the remaining mismatch.

The nonmatching active source and generated report were removed. This directory contains only this README and the complete recovered C. No byte-exact match is claimed.
