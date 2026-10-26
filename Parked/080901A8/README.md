# 080901A8 — Parked

Target and candidate complete extent: 0x080901A8..0x08090214, 108 bytes / 54 reachable Thumb instructions. No calls, relocations or literal pool.

The recovered function writes mirrored two-byte gradient entries around a signed-halfword center (state offset 4), starting at signed radius (offset 6) and counting down through zero. A signed extent at offset 8 defines the coefficients: offsets at or beyond extent receive (0,16); positive inward distance at most eight receives (16,16-distance); larger inward distance receives (16,9). Distance is compared unsigned. Both coefficients narrow to bytes; center plus/minus offset narrows to s16 before the two-byte scaling. The output byte-buffer pointer is at state offset 0.

Fresh default native matcher with agbcc `-mthumb-interwork -O2`: exit 1, source plausible, complete symbol 108 bytes, bytes differ. The native alignment score is 36/54 instructions and 85/108 bytes; this is not same-offset equality.

The candidate reproduces the control flow, 16-bit arithmetic conversion, byte conversions, signed mirrored indexing, four byte stores, two per-pair pointer increments, no-frame leaf shape, and instruction count. The remaining gap is register allocation and dependent address operand choices: target holds first/second bytes in r3/r4 and buffer in r2; candidate uses r2/r3 and r4 respectively. Target address additions retain the buffer register as their first input and final destination where appropriate, while candidate additions retain the scaled index. State and outer offset are r6/r5 in both.

Bounded natural attempts tested an ordinary two-member struct (agbcc gives a four-byte entry stride and word copies), a two-byte array with direct member stores (correct stride but repeated state loads), cached byte-buffer views (100-byte leaf because adjacent stores coalesce), and explicit advancing byte pointers (preserved 108-byte leaf). Equivalent pointer-add versus subscript expressions and pointer-cache placement did not resolve the allocation. A packed two-byte struct was also checked: fixed compilation emits a four-byte stack frame and two memcpy calls, so the native matcher correctly rejects an unaddressed runtime call. This was not a parser defect, and no helper or toolkit bypass was attempted. No assembly, volatile accesses, dead operations, altered compiler flags, or shared edits were used.

The tested source is preserved here; owned unmatched active source and report were removed. Final native evidence remains in the address scratch directory. No exact-match credit is claimed.
